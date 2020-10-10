/*
 * collision_system.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "collision_system.h"
#include "../components/collision.h"
#include "../components/interaction.h"
#include "../entity.h"
#include "../math_ext.h"
#include "../commands/select_entity_command.h"
#include "../commands/call_procedure_command.h"
#include "../components/absolute_position.h"
#include <algorithm>
#include <unordered_set>
#include "systems.h"
#include "command_system.h"
#include "entity_system.h"

struct CorrectionValues
{
	CorrectionValues() : x{0}, y{0}, vx{0}, vy{0} {}
	double x, y, vx, vy;
};

void CollisionSystem::update(const Time time_diff)
{
	for(const auto entity_id : entities)
	{
		auto& interaction = system<EntitySystem>().entity_component<Interaction>(entity_id);
		interaction.update_last_triggered_groups();
	}

	//register+unregister entities from regions
	for(const auto entity_id : entities)
	{
		const auto& position = system<EntitySystem>().entity_component<Position>(entity_id);
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

	std::unordered_map<EntityID, CorrectionValues> collision_correction;

	for(const auto entity_id : entities)
	{
		const auto& collision = system<EntitySystem>().entity_component<Collision>(entity_id);
		if(collision.state() == Collision::CollisionState::MOVEABLE)
			collision_correction.insert(std::make_pair(entity_id, CorrectionValues{}));
	}

	for(const auto id0 : entities)
	{
		auto& collision0 = system<EntitySystem>().entity_component<Collision>(id0);
		if(collision0)
		{
			auto& interaction0 = system<EntitySystem>().entity_component<Interaction>(id0);
			auto& position0 = system<EntitySystem>().entity_component<Position>(id0);

			collision0.set_standing_on(Collision::AIR);
			const Collision::RegionLocation& location0 = regions_per_entity[id0];

			std::unordered_set<EntityID> near_entities;

			for(int region_x = location0.x; region_x < location0.x_end; ++region_x)
				for(int region_y = location0.y; region_y < location0.y_end; ++region_y)
					for(const auto entity_id : entities_per_region[RegionPosition{region_x, region_y}])
						near_entities.insert(entity_id);

			near_entities.erase(id0); //remove self from the set

			const double x1 = position0.x() + position0.w();
			const double y1 = position0.y() + position0.h();

			for(const auto id1 : near_entities)
			{
				const auto& collision1 = system<EntitySystem>().entity_component<Collision>(id1);
				if(collision1 && id1 != id0)
				{
					const auto& position1 = system<EntitySystem>().entity_component<Position>(id1);

					if(objects_collide(position0.x(), position0.y(), position0.w(), position0.h()
									 , position1.x(), position1.y(), position1.w(), position1.h()
									  )
					  )
					{
						//entities collide
						const auto& interaction1 = system<EntitySystem>().entity_component<Interaction>(id1);

						interaction0.set_triggered_groups(interaction1.group_vector());

						if(interaction1.is_in_group(interaction0.trigger_group()))
						{
							if(interaction0.proc_id_other() >= 0)
							{
								system<CommandSystem>().push(std::make_unique<SelectEntityCommand>(id1));
								system<CommandSystem>().push(std::make_unique<CallProcedureCommand>(interaction0.proc_id_other()));
							}
						}

						if(interaction0.is_in_group(interaction1.trigger_group()))
						{
							if(interaction1.proc_id_other() >= 0)
							{
								system<CommandSystem>().push(std::make_unique<SelectEntityCommand>(id1));
								system<CommandSystem>().push(std::make_unique<CallProcedureCommand>(interaction1.proc_id_other()));
							}
						}

						system<EntitySystem>().entity_component<Health>(id0).mod_hp_change(-collision1.on_collision_damage()*time_diff);

						const bool entity0_correctable = (collision0.state() == Collision::MOVEABLE)
													  && (collision1.state() >= Collision::MOVEABLE);

						if(entity0_correctable)
						{
							const auto& movement0 = system<EntitySystem>().entity_component<Movement>(id0);
							const auto& movement1 = system<EntitySystem>().entity_component<Movement>(id1);
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
			//error *it0
		}

	}

	for(const auto entity_pair : collision_correction)
	{
		auto& position = system<EntitySystem>().entity_component<Position>(entity_pair.first);
		auto& movement = system<EntitySystem>().entity_component<Movement>(entity_pair.first);
		position.mod_x(entity_pair.second.x);
		position.mod_y(entity_pair.second.y);
		movement.mod_dx(entity_pair.second.x);
		movement.mod_dy(entity_pair.second.y);
		movement.mod_velocity_x(entity_pair.second.vx);
		movement.mod_velocity_y(entity_pair.second.vy);
	}

	for(const auto id : entities)
	{
		const auto& interaction = system<EntitySystem>().entity_component<Interaction>(id);
		if(interaction)
		{
			const bool last_triggered = (interaction.last_triggered_groups() >> interaction.trigger_group())%2;
			const bool triggered      = (interaction.triggered_groups()      >> interaction.trigger_group())%2;
			if(triggered != last_triggered)
			{
				if(triggered && interaction.proc_id_self() >= 0)
				{
					system<CommandSystem>().push(std::make_unique<SelectEntityCommand>(id));
					system<CommandSystem>().push(std::make_unique<CallProcedureCommand>(interaction.proc_id_self()));
				}
				else if(!triggered && interaction.on_exit_proc_id_self() >= 0)
				{
					system<CommandSystem>().push(std::make_unique<SelectEntityCommand>(id));
					system<CommandSystem>().push(std::make_unique<CallProcedureCommand>(interaction.on_exit_proc_id_self()));
				}
			}
		}
	}
}
