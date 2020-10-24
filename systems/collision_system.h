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

template<typename EntitySystemT>
class CollisionSystem : public SystemBase
{
public:

	CollisionSystem(EntitySystemT& entity_system) : m_entity_system(entity_system) {}

	void update(const Time time_diff, EntitySystemT& entity_system, std::list<std::pair<EntityID, AbsProcedureID>>& procedure_calls)
	{
		for(const auto entity_id : entities)
		{
			Interaction& interaction = entity_system.entity_component(entity_id, (Interaction*)nullptr);
			interaction.update_last_triggered_groups();
		}

		//register+unregister entities from regions
		for(const auto entity_id : entities)
		{
			const Position& position = entity_system.entity_component(entity_id, (Position*)nullptr);
			if(position)
			{
				const Collision::RegionLocation& old_location = regions_per_entity[entity_id];
				const Collision::RegionLocation new_location
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

		std::unordered_map<AbsEntityID, CorrectionValues> collision_correction;

		for(const auto entity_id : entities)
		{
			const auto& collision = entity_system.entity_component(entity_id, (Collision*)nullptr);
			if(collision.state() == Collision::CollisionState::MOVEABLE)
				collision_correction.insert(std::make_pair(entity_id, CorrectionValues{}));
		}

		for(const auto id0 : entities)
		{
			auto& collision0 = entity_system.entity_component(id0, (Collision*)nullptr);
			if(collision0)
			{
				auto& interaction0 = entity_system.entity_component(id0, (Interaction*)nullptr);
				const auto& position0 = entity_system.entity_component(id0, (Position*)nullptr);

				collision0.set_standing_on(Collision::AIR);
				const Collision::RegionLocation& location0 = regions_per_entity[id0];

				std::unordered_set<AbsEntityID> near_entities;

				for(int region_x = location0.x; region_x < location0.x_end; ++region_x)
					for(int region_y = location0.y; region_y < location0.y_end; ++region_y)
						for(const auto entity_id : entities_per_region[RegionPosition{region_x, region_y}])
							near_entities.insert(entity_id);

				near_entities.erase(id0); //remove self from the set

				const double x1 = position0.x() + position0.w();
				const double y1 = position0.y() + position0.h();

				for(const auto id1 : near_entities)
				{
					const auto& collision1 = entity_system.entity_component(id1, (Collision*)nullptr);
					if(collision1 && id1 != id0)
					{
						const auto& position1 = entity_system.entity_component(id1, (Position*)nullptr);

						if(objects_collide(position0.x(), position0.y(), position0.w(), position0.h()
										 , position1.x(), position1.y(), position1.w(), position1.h()
										  )
						  )
						{
							//entities collide
							const auto& interaction1 = entity_system.entity_component(id1, (Interaction*)nullptr);

							interaction0.set_triggered_groups(interaction1.group_vector());

							if(interaction1.is_in_group(interaction0.trigger_group()))
							{
								if(interaction0.proc_id_other() >= 0)
									procedure_calls.emplace_back(id1, interaction0.proc_id_other());
							}

							if(interaction0.is_in_group(interaction1.trigger_group()))
							{
								if(interaction1.proc_id_other() >= 0)
									procedure_calls.emplace_back(id0, interaction1.proc_id_other());
							}

							entity_system.entity_component(id0, (Health*)nullptr).mod_hp_change(-collision1.on_collision_damage()*time_diff);

							const bool entity0_correctable = (collision0.state() == Collision::MOVEABLE)
														  && (collision1.state() >= Collision::MOVEABLE);

							if(entity0_correctable)
							{
								const auto& movement0 = entity_system.entity_component(id0, (Movement*)nullptr);
								const auto& movement1 = entity_system.entity_component(id1, (Movement*)nullptr);
								const double dx = movement1.dx() - movement0.dx();
								const double dy = movement1.dy() - movement0.dy();

								const double x2 = position1.x();
								const double y2 = position1.y();
								const double sw = position1.w() + position0.w();
								const double sh = position1.h() + position0.h();

								const double dvx = 2*(movement1.vx()-movement0.vx())*((collision1.state()==Collision::CollisionState::SOLID) ? 1 : movement1.mass()/(movement0.mass()+movement1.mass()))*collision0.elasticity()*collision1.elasticity();
								const double dvy = 2*(movement1.vy()-movement0.vy())*((collision1.state()==Collision::CollisionState::SOLID) ? 1 : movement1.mass()/(movement0.mass()+movement1.mass()))*collision0.elasticity()*collision1.elasticity();

								if(dy > 0)
								{
									const double t = clip(lines_cross(x1, y1, dx, dy, x2, y2+sh, sw, 0), -1.0, 1.0);
									if(t >= 0.0)
									{
										collision_correction[id0].y = t*((collision1.state()==Collision::CollisionState::SOLID)*movement1.dy() - movement0.dy());
										collision_correction[id0].vy += dvy;
										collision0.set_standing_on(Collision::GROUND);
									}
								}
								else if(dy < 0)
								{
									const double t = lines_cross(x1, y1, dx, dy, x2, y2, sw, 0);
									if(t >= 0.0)
									{
										collision_correction[id0].y = t*((collision1.state()==Collision::CollisionState::SOLID)*movement1.dy() - movement0.dy());
										collision_correction[id0].vy += dvy;
									}
								}


								if(dx < 0)
								{
									const double t = clip(lines_cross(x1, y1, dx, dy, x2, y2, 0, sh), -1.0, 1.0);
									if(t >= 0.0)
									{
										collision_correction[id0].x = t*((collision1.state()==Collision::CollisionState::SOLID)*movement1.dx()- movement0.dx());
										collision_correction[id0].vx += dvx;
									}
								}
								else if(dx > 0)
								{
									const double t = clip(lines_cross(x1, y1, dx, dy, x2+sw, y2, 0, sh), -1.0, 1.0);
									if(t >= 0.0)
									{
										collision_correction[id0].x = t*((collision1.state()==Collision::CollisionState::SOLID)*movement1.dx() - movement0.dx());
										collision_correction[id0].vx += dvx;
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

		for(const auto entity_pair : collision_correction)
		{
			auto& position = entity_system.entity_component(entity_pair.first, (Position*)nullptr);
			auto& movement = entity_system.entity_component(entity_pair.first, (Movement*)nullptr);
			position.mod_x(entity_pair.second.x);
			position.mod_y(entity_pair.second.y);
			movement.mod_dx(entity_pair.second.x);
			movement.mod_dy(entity_pair.second.y);
			movement.mod_velocity_x(entity_pair.second.vx);
			movement.mod_velocity_y(entity_pair.second.vy);
		}

		for(const auto id : entities)
		{
			const Interaction& interaction = entity_system.entity_component(id, (Interaction*)nullptr);
			if(interaction)
			{
				const bool last_triggered = (interaction.last_triggered_groups() >> interaction.trigger_group())%2;
				const bool triggered      = (interaction.triggered_groups()      >> interaction.trigger_group())%2;
				if(triggered != last_triggered)
				{
					if(triggered && interaction.proc_id_self() >= 0)
						procedure_calls.emplace_back(id, interaction.proc_id_self());
					else if(!triggered && interaction.on_exit_proc_id_self() >= 0)
						procedure_calls.emplace_back(id, interaction.on_exit_proc_id_self());
				}
			}
		}
	}

    template<typename T>
    void component_updated(const T& component, const AbsEntityID id, const int8_t change)
    {
    	if constexpr(std::is_same<T, Collision>::value)
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
    		return std::hash<int>()(p.x) ^ std::hash<int>()(p.y); // @suppress("std::hash<int> is ambiguous")
    	}
    };

    struct CorrectionValues
    {
    	CorrectionValues() : x{0}, y{0}, vx{0}, vy{0} {}
    	double x, y, vx, vy;
    };

    EntitySystemT& m_entity_system;
    std::unordered_map<RegionPosition, std::unordered_set<AbsEntityID>, RegionPositionHashFn> entities_per_region;
    std::unordered_map<AbsEntityID, Collision::RegionLocation> regions_per_entity;
	static const unsigned int REGION_W = 32;
    static const unsigned int REGION_H = 32;
};

#endif /* SYSTEMS_COLLISION_SYSTEM_H_ */
