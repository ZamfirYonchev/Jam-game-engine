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
#include "../globals.h"
#include "../math_ext.h"
#include "../commands/select_entity_command.h"
#include "../commands/call_procedure_command.h"
#include "../components/absolute_position.h"
#include <algorithm>
#include <unordered_set>

struct CorrectionValues
{
	CorrectionValues() : x{0}, y{0}, vx{0}, vy{0} {}
	double x, y, vx, vy;
};

void CollisionSystem::update(const Time time_diff)
{
	for(const auto entity_id : entities)
	{
		auto entity_optional = entity_system().entity(entity_id);
		if(entity_optional)
		{
			entity_optional->interaction()->update_last_triggered_groups();
		}
		else
		{
			//error
		}
	}

	//register+unregister entities from regions
	for(const auto entity_id : entities)
	{
		auto entity_optional = entity_system().entity(entity_id);
		if(entity_optional)
		{
			Entity& entity = *entity_optional;
			const Position* position = entity.position();

			const Collision::RegionLocation& old_location = entity.collision()->region_location();
			const Collision::RegionLocation new_location
			{
				int(std::floor(position->x() / REGION_W)),
				int(std::floor(position->y() / REGION_W)),
				int(std::ceil((position->x()+position->w()) / REGION_W)),
				int(std::ceil((position->y()+position->h()) / REGION_H))
			};

			if(old_location != new_location)
			{
				for(int region_x = old_location.x; region_x < old_location.x_end; ++region_x)
					for(int region_y = old_location.y; region_y < old_location.y_end; ++region_y)
						entity_regions[RegionPosition{region_x, region_y}].erase(entity_id);

				entity.collision()->set_region_location(new_location);

				for(int region_x = new_location.x; region_x < new_location.x_end; ++region_x)
					for(int region_y = new_location.y; region_y < new_location.y_end; ++region_y)
						entity_regions[RegionPosition{region_x, region_y}].insert(entity_id);
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
		const auto entity_optional = entity_system().entity(entity_id);
		if(entity_optional && entity_optional->collision()->state() == Collision::CollisionState::MOVEABLE)
			collision_correction.insert(std::make_pair(entity_id, CorrectionValues{}));
	}

	for(auto it0 = cbegin(entities); it0 != cend(entities); ++it0)
	{
		auto entity_optional = entity_system().entity(*it0);
		if(entity_optional)
		{
			Entity& entity0 = *entity_optional;
			Collision* collision0 = entity0.collision();
			Interaction* interaction0 = entity0.interaction();

			collision0->set_standing_on(Collision::AIR);
			const Collision::RegionLocation& location0 = collision0->region_location();

			std::unordered_set<EntityID> near_entities;

			for(int region_x = location0.x; region_x < location0.x_end; ++region_x)
				for(int region_y = location0.y; region_y < location0.y_end; ++region_y)
					for(const auto entity_id : entity_regions[RegionPosition{region_x, region_y}])
						near_entities.insert(entity_id);

			near_entities.erase(*it0); //remove self from the set

			const double x1 = entity0.position()->x() + entity0.position()->w();
			const double y1 = entity0.position()->y() + entity0.position()->h();

			for(auto it1 = cbegin(near_entities); it1 != cend(near_entities); ++it1)
			{
				const auto entity1_optional = entity_system().entity(*it1);
				if(entity1_optional && entity1_optional->id() != entity0.id())
				{
					const Entity& entity1 = *entity1_optional;
					const Collision* collision1 = entity1.collision();

					if(objects_collide(entity0.position()->x(), entity0.position()->y(), entity0.position()->w(), entity0.position()->h()
									 , entity1.position()->x(), entity1.position()->y(), entity1.position()->w(), entity1.position()->h()
									  )
					  )
					{
						//entities collide
						const Interaction* interaction1 = entity1.interaction();

						interaction0->set_triggered_groups(interaction1->group_vector());

						if(interaction1->is_in_group(interaction0->trigger_group()))
						{
							if(interaction0->proc_id_other() >= 0)
							{
								command_queue().push(std::make_unique<SelectEntityCommand>(entity1.id()));
								command_queue().push(std::make_unique<CallProcedureCommand>(interaction0->proc_id_other()));
							}
						}

						if(interaction0->is_in_group(interaction1->trigger_group()))
						{
							if(interaction1->proc_id_other() >= 0)
							{
								command_queue().push(std::make_unique<SelectEntityCommand>(entity0.id()));
								command_queue().push(std::make_unique<CallProcedureCommand>(interaction1->proc_id_other()));
							}
						}

						entity0.health()->mod_hp_change(-collision1->on_collision_damage()*time_diff);

						const bool entity0_correctable = (collision0->state() == Collision::MOVEABLE)
													  && (collision1->state() >= Collision::MOVEABLE);

						if(entity0_correctable)
						{
							const double dx = entity1.movement()->dx() - entity0.movement()->dx();
							const double dy = entity1.movement()->dy() - entity0.movement()->dy();

							const double x2 = entity1.position()->x();
							const double y2 = entity1.position()->y();
							const double sw = entity1.position()->w() + entity0.position()->w();
							const double sh = entity1.position()->h() + entity0.position()->h();

							const double dvx = 2*(entity1.movement()->vx()-entity0.movement()->vx())*((entity1.collision()->state()==Collision::CollisionState::SOLID) ? 1 : entity1.movement()->mass()/(entity0.movement()->mass()+entity1.movement()->mass()))*collision0->elasticity()*collision1->elasticity();
							const double dvy = 2*(entity1.movement()->vy()-entity0.movement()->vy())*((entity1.collision()->state()==Collision::CollisionState::SOLID) ? 1 : entity1.movement()->mass()/(entity0.movement()->mass()+entity1.movement()->mass()))*collision0->elasticity()*collision1->elasticity();

							if(dy > 0)
							{
								const double t = clip(lines_cross(x1, y1, dx, dy, x2, y2+sh, sw, 0), -1.0, 1.0);
								if(t >= 0.0)
								{
									collision_correction[entity0.id()].y = t*((entity1.collision()->state()==Collision::CollisionState::SOLID)*entity1.movement()->dy()- entity0.movement()->dy());
									collision_correction[entity0.id()].vy += dvy;
									collision0->set_standing_on(Collision::GROUND);
								}
							}
							else if(dy < 0)
							{
								const double t = lines_cross(x1, y1, dx, dy, x2, y2, sw, 0);
								if(t >= 0.0)
								{
									collision_correction[entity0.id()].y = t*((entity1.collision()->state()==Collision::CollisionState::SOLID)*entity1.movement()->dy()- entity0.movement()->dy());
									collision_correction[entity0.id()].vy += dvy;
								}
							}


							if(dx < 0)
							{
								const double t = clip(lines_cross(x1, y1, dx, dy, x2, y2, 0, sh), -1.0, 1.0);
								if(t >= 0.0)
								{
									collision_correction[entity0.id()].x = t*((entity1.collision()->state()==Collision::CollisionState::SOLID)*entity1.movement()->dx()- entity0.movement()->dx());
									collision_correction[entity0.id()].vx += dvx;
								}
							}
							else if(dx > 0)
							{
								const double t = clip(lines_cross(x1, y1, dx, dy, x2+sw, y2, 0, sh), -1.0, 1.0);
								if(t >= 0.0)
								{
									collision_correction[entity0.id()].x = t*((entity1.collision()->state()==Collision::CollisionState::SOLID)*entity1.movement()->dx()- entity0.movement()->dx());
									collision_correction[entity0.id()].vx += dvx;
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
		Position* position = entity_system().entity(entity_pair.first)->position();
		Movement* movement = entity_system().entity(entity_pair.first)->movement();
		position->mod_x(entity_pair.second.x);
		position->mod_y(entity_pair.second.y);
		movement->mod_dx(entity_pair.second.x);
		movement->mod_dy(entity_pair.second.y);
		movement->mod_velocity_x(entity_pair.second.vx);
		movement->mod_velocity_y(entity_pair.second.vy);
	}

	for(const auto id : entities)
	{
		auto entity_optional = entity_system().entity(id);
		if(entity_optional)
		{
			const Interaction* interaction = entity_optional->interaction();
			const bool last_triggered = (interaction->last_triggered_groups() >> interaction->trigger_group())%2;
			const bool triggered      = (interaction->triggered_groups()      >> interaction->trigger_group())%2;
			if(triggered != last_triggered)
			{
				if(triggered && interaction->proc_id_self() >= 0)
				{
					command_queue().push(std::make_unique<SelectEntityCommand>(id));
					command_queue().push(std::make_unique<CallProcedureCommand>(interaction->proc_id_self()));
				}
				else if(!triggered && interaction->on_exit_proc_id_self() >= 0)
				{
					command_queue().push(std::make_unique<SelectEntityCommand>(id));
					command_queue().push(std::make_unique<CallProcedureCommand>(interaction->on_exit_proc_id_self()));
				}
			}
		}
	}
}
