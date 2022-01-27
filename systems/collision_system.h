/*
 * collision_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_COLLISION_SYSTEM_H_
#define SYSTEMS_COLLISION_SYSTEM_H_

#include "system_base.h"
#include <unordered_map>
#include <unordered_set>
#include "../components/collision.h"
#include "../components/interaction.h"
#include "../components/health.h"
#include "../components/movement.h"
#include "../math_ext.h"
#include <list>
#include <utility>
#include <type_traits>

template<typename EntitySystemT, typename PositionT, typename MovementT, typename CollisionT, typename InteractionT, typename HealthT>
class CollisionSystem : public SystemBase
{
	struct RegionLocation
	{
		int x, y;
		int x_end, y_end;
		RegionLocation() : x{0}, y{0}, x_end{0}, y_end{0} {}
		RegionLocation(int _x, int _y, int _x_end, int _y_end) : x{_x}, y{_y}, x_end{_x_end}, y_end{_y_end} {}

		bool operator==(const RegionLocation& rhs) const
		{
			return (x==rhs.x) && (y==rhs.y) && (x_end==rhs.x_end) && (y_end==rhs.y_end);
		}

		bool operator!=(const RegionLocation& rhs) const { return !(*this == rhs); }

		bool is_null() const { return (x==x_end) || (y==y_end); }
	};

public:
    constexpr static double GRAVITY_ACCEL = -0.00980665; //always (IRL, 9.80665m/s^2 = 0.00980665mm/ms^2)

	CollisionSystem(EntitySystemT& entity_system, Globals& _globals, std::stringstream& _external_commands)
    : m_entity_system(entity_system)
    , globals{_globals}
	, external_commands{_external_commands}
	{}

	void update(const Time time_diff)
	{
		if(globals(Globals::app_paused).boolean()) return;

		for(const auto entity_id : entities)
		{
			auto& interaction = m_entity_system.template entity_component<InteractionT>(entity_id);
			interaction.update_last_triggered_groups();
		}

		//register+unregister entities from regions
		for(const auto entity_id : entities)
		{
			const auto& position = m_entity_system.template entity_component<PositionT>(entity_id);
			if(position)
			{
				const RegionLocation& old_location = regions_per_entity[entity_id];
				const RegionLocation new_location
				{
					int(std::floor(position.x() / REGION_W)),
					int(std::floor(position.y() / REGION_W)),
					int(std::ceil((position.x()+position.w()) / REGION_W)),
					int(std::ceil((position.y()+position.h()) / REGION_H))
				};

				if(old_location != new_location)
				{
					for(int region_x = old_location.x; region_x < old_location.x_end; ++region_x)
						for(int region_y = old_location.y; region_y < old_location.y_end; ++region_y)
							entities_per_region[RegionPosition{region_x, region_y}].erase(entity_id);

					for(int region_x = new_location.x; region_x < new_location.x_end; ++region_x)
						for(int region_y = new_location.y; region_y < new_location.y_end; ++region_y)
							entities_per_region[RegionPosition{region_x, region_y}].insert(entity_id);

					regions_per_entity[entity_id] = new_location;
				}
			}
			else
			{
				//error
			}
		}

		std::unordered_map<EntityID, CorrectionValues> collision_correction;

		for(const auto entity_id : entities)
			collision_correction.insert(std::make_pair(entity_id, CorrectionValues{}));

		for(const auto id0 : entities)
		{
			auto& collision0 = m_entity_system.template entity_component<CollisionT>(id0);
			if(collision0)
			{
				auto& interaction0 = m_entity_system.template entity_component<InteractionT>(id0);
				const auto& position0 = m_entity_system.template entity_component<PositionT>(id0);

				collision0.set_standing_on(SurfaceType::AIR);

				const RegionLocation& location0 = regions_per_entity[id0];

				std::unordered_set<EntityID> near_entities;

				for(int region_x = location0.x; region_x < location0.x_end; ++region_x)
					for(int region_y = location0.y; region_y < location0.y_end; ++region_y)
						for(const auto entity_id : entities_per_region[RegionPosition{region_x, region_y}])
							near_entities.insert(entity_id);

				near_entities.erase(id0); //remove self from the set

				const auto& movement0 = m_entity_system.template entity_component<MovementT>(id0);
				CorrectionValues& correction_values = collision_correction[id0];

				for(const auto id1 : near_entities)
				{
					const auto& collision1 = m_entity_system.template entity_component<CollisionT>(id1);
					if(collision1 && id1 != id0)
					{
						const auto& position1 = m_entity_system.template entity_component<PositionT>(id1);

						if(objects_collide(position0.x(), position0.y(), position0.w(), position0.h()
										 , position1.x(), position1.y(), position1.w(), position1.h()
										  )
						  )
						{
							//entities collide
							const auto& interaction1 = m_entity_system.template entity_component<InteractionT>(id1);

							interaction0.set_triggered_groups(interaction1.group_vector());

							if(interaction1.is_in_group(interaction0.trigger_group()))
							{
								if(interaction0.proc_id_other() > 0)
									external_commands << "Select " << id1 <<  " Call " << interaction0.proc_id_other() << '\n';
							}

							if(interaction0.is_in_group(interaction1.trigger_group()))
							{
								if(interaction1.proc_id_other() > 0)
									external_commands << "Select " << id0 <<  " Call " << interaction1.proc_id_other() << '\n';
							}

							m_entity_system.template entity_component<HealthT>(id0).mod_hp(-collision1.on_collision_damage()*time_diff);

							const bool entity0_correctable = movement0 && collision0.solid() && collision1.solid();

							if(entity0_correctable)
							{
								const auto& movement1 = m_entity_system.template entity_component<MovementT>(id1);
								const double weight_coeff = movement1.mass()/(movement0.mass()+movement1.mass());

								const double dx = movement1.dx() - movement0.dx();
								const double dy = movement1.dy() - movement0.dy();

								/*          __________________sw,sh
								 *         |                  |
								 *         |                  |
								 *      h0 |                  |
								 *         |___w1____         |
								 *         |         |        |
								 *     ____|___pxpy  | h1     |
								 *    |    |   |     |        |
								 *    |    |___|_____|________|
								 * h0 |  0,0   |         w0
								 *    |________|
								 * x0y0   w0
								 */

								const double sw = position1.w() + position0.w();
								const double sh = position1.h() + position0.h();
								const double px = position0.x() + position0.w() - position1.x();
								const double py = position0.y() + position0.h() - position1.y();

								const double overlap_corr = min(min(px, sw-px), min(py, sh-py));

								const double overlap_corr_x = (overlap_corr == px) ? -px :
															  (overlap_corr == sw-px) ? sw-px : 0;

								const double overlap_corr_y = (overlap_corr == py) ? -py :
															  (overlap_corr == sh-py) ? sh-py : 0;

								const double dvx_half = (movement1.vx()-movement0.vx())*weight_coeff;
								const double dvy_half = (movement1.vy()-movement0.vy())*weight_coeff;

								correction_values.x += overlap_corr_x*weight_coeff;
								correction_values.y += overlap_corr_y*weight_coeff;

								if(dy > 0)
								{
									const double t = lines_cross(px, py, dx, dy, 0, sh, sw, 0);

									if(t >= 0.0)
									{
										correction_values.vy += dvy_half*(1+collision0.elasticity()*collision1.elasticity());
										correction_values.vx += dvx_half*2*movement0.friction_x()*movement1.friction_x();

										collision0.set_standing_on(SurfaceType::GROUND);
									}
								}
								else if(dy < 0)
								{
									const double t = lines_cross(px, py, dx, dy, 0, 0, sw, 0);
									if(t >= 0.0)
									{
										correction_values.vy += dvy_half*(1+collision0.elasticity()*collision1.elasticity());
										correction_values.vx += dvx_half*2*movement0.friction_x()*movement1.friction_x();
									}
								}


								if(dx < 0)
								{
									const double t = lines_cross(px, py, dx, dy, 0, 0, 0, sh);
									if(t >= 0.0)
									{
										correction_values.vx += dvx_half*(1+collision0.elasticity()*collision1.elasticity());
										correction_values.vy += dvy_half*2*movement0.friction_y()*movement1.friction_y();
									}
								}
								else if(dx > 0)
								{
									const double t = lines_cross(px, py, dx, dy, sw, 0, 0, sh);
									if(t >= 0.0)
									{
										correction_values.vx += dvx_half*(1+collision0.elasticity()*collision1.elasticity());
										correction_values.vy += dvy_half*2*movement0.friction_y()*movement1.friction_y();
									}
								}
							}
						}
					}
				}
			}
			else
			{
				//error id0
			}

		}

		for(const auto& entity_pair : collision_correction)
		{
			auto& movement = m_entity_system.template entity_component<MovementT>(entity_pair.first);
			auto& position = m_entity_system.template entity_component<PositionT>(entity_pair.first);
			position.mod_x(entity_pair.second.x);
			position.mod_y(entity_pair.second.y);
			movement.mod_dx(entity_pair.second.x);
			movement.mod_dy(entity_pair.second.y);
			movement.mod_velocity_x(entity_pair.second.vx);
			movement.mod_velocity_y(entity_pair.second.vy);
		}

		for(const auto id : entities)
		{
			const auto& interaction = m_entity_system.template entity_component<InteractionT>(id);
			if(interaction)
			{
				const bool last_triggered = (interaction.last_triggered_groups() >> interaction.trigger_group())%2;
				const bool triggered      = (interaction.triggered_groups()      >> interaction.trigger_group())%2;
				if(triggered != last_triggered)
				{
					if(triggered && interaction.proc_id_self() > 0)
						external_commands << "Select " << id <<  " Call " << interaction.proc_id_self() << '\n';
					else if(!triggered && interaction.on_exit_proc_id_self() > 0)
						external_commands << "Select " << id <<  " Call " << interaction.on_exit_proc_id_self() << '\n';
				}
			}
		}
	}

    template<typename T>
    void component_updated
	( [[maybe_unused]] const T& component
	, [[maybe_unused]] const EntityID id
	, [[maybe_unused]] const int8_t change
	)
    {
    	if constexpr(std::is_same<T, CollisionT>::value)
		{
    		if(change < 0)
    			remove_id(id);
    		else if(change > 0)
    			add_id(id);
		}
    }

    void clear()
    {
    	SystemBase::clear();
    	entities_per_region.clear();
    	regions_per_entity.clear();
    }

private:
    struct RegionPosition
	{
    	int x; int y;

    	constexpr bool operator==(const RegionPosition &p) const
    	{
    		return x == p.x && y == p.y;
    	}

    	constexpr bool operator!=(const RegionPosition &p) const
		{
    		return !(*this == p);
		}

	};

    struct RegionPositionHashFn
    {
    	std::size_t operator() (const RegionPosition &p) const
    	{
    		return std::hash<int>()(p.x) ^ std::hash<int>()(p.y); // @suppress("Ambiguous problem")
    	}
    };

    struct CorrectionValues
    {
    	CorrectionValues() : x{0}, y{0}, vx{0}, vy{0} {}

    	double x, y, vx, vy;
    };


    EntitySystemT& m_entity_system;
    Globals& globals;
    std::stringstream& external_commands;
    std::unordered_map<RegionPosition, std::unordered_set<EntityID>, RegionPositionHashFn> entities_per_region;
    std::unordered_map<EntityID, RegionLocation> regions_per_entity;
	static const unsigned int REGION_W = 32;
    static const unsigned int REGION_H = 32;
};

#endif /* SYSTEMS_COLLISION_SYSTEM_H_ */
