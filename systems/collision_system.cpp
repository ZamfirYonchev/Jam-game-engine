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
#include <algorithm>

void CollisionSystem::update(const Time time_diff)
{
	const std::unordered_map<EntityID, bool> entity_last_triggered {entities_last_triggered_reset()};

	for(auto it0 = entities.begin(); it0 != entities.end(); ++it0)
        for(auto it1 = std::next(it0); it1 != entities.end(); ++it1)
        {
        	if(entity_system().entity(*it0) && entity_system().entity(*it1))
        	{
				Entity& entity0 = *(entity_system().entity(*it0));
				Entity& entity1 = *(entity_system().entity(*it1));
				Collision* collision0 = entity0.collision();
				Collision* collision1 = entity1.collision();

				double x0 = entity0.position()->x();
				double y0 = entity0.position()->y();
				double x3 = entity1.position()->x() + entity1.position()->w();
				double y3 = entity1.position()->y() + entity1.position()->h();
				double sx = entity0.position()->x() + entity0.position()->w() + entity1.position()->w();
				double sy = entity0.position()->y() + entity0.position()->h() + entity1.position()->h();

				if(objects_collide(entity0.position()->x(), entity0.position()->y(), entity0.position()->w(), entity0.position()->h()
								 , entity1.position()->x(), entity1.position()->y(), entity1.position()->w(), entity1.position()->h()
								  )
				  )
				{
					//entities collide
					Interaction* interaction0 = entity0.interaction();
					Interaction* interaction1 = entity1.interaction();

					if(interaction1->is_in_group(interaction0->trigger_group()))
					{
						interaction0->set_triggered(true);
						if(interaction0->proc_id_other() >= 0)
						{
							command_queue().push(std::make_unique<SelectEntityCommand>(entity1.id()));
							command_queue().push(std::make_unique<CallProcedureCommand>(interaction0->proc_id_other()));
						}
					}

					if(interaction0->is_in_group(interaction1->trigger_group()))
					{
						interaction1->set_triggered(true);
						if(interaction1->proc_id_other() >= 0)
						{
							command_queue().push(std::make_unique<SelectEntityCommand>(entity0.id()));
							command_queue().push(std::make_unique<CallProcedureCommand>(interaction1->proc_id_other()));
						}
					}

					entity0.health()->mod_hp_change(-collision1->on_collision_damage()*time_diff);
					entity1.health()->mod_hp_change(-collision0->on_collision_damage()*time_diff);

					const bool objects_collide = (collision0->state() >= Collision::MOVEABLE)
										&& (collision1->state() >= Collision::MOVEABLE)
										&& (collision0->state() != collision1->state());

					if(objects_collide)
					{
						Entity& moving_entity = collision0->state() == Collision::MOVEABLE ? entity0 : entity1;
						const double dx = time_diff*(entity0.movement()->vx() - entity1.movement()->vx());
						const double dy = time_diff*(entity0.movement()->vy() - entity1.movement()->vy());
						double t;

						t = lines_cross(x3, y3, dx, dy, x0, sy, sx-x0, 0);
						if(t >= 0.0)
						{
							moving_entity.position()->mod_y(-sign(moving_entity.movement()->vy())*(sy-y3));
							//moving_entity->movement()->mod_velocity_y(-sign(moving_entity->movement()->vy())*(sy-y3)/time_diff);
							moving_entity.movement()->set_velocity_y(0);
							if(entity1.id() == moving_entity.id())
							{
								moving_entity.collision()->set_standing_on(Collision::GROUND);
								moving_entity.movement()->mod_force_x(0.02*dx/time_diff);
							}
						}
						else
						{
							t = lines_cross(x3, y3, dx, dy, x0, y0, 0, sy-y0);
							if(t >= 0.0)
							{
								moving_entity.position()->mod_x(-sign(moving_entity.movement()->vx())*(x3-x0));
								//moving_entity->movement()->mod_velocity_x(-sign(moving_entity->movement()->vx())*(x3-x0)/time_diff);
								moving_entity.movement()->set_velocity_x(0);
						   }
							else
							{
								t = lines_cross(x3, y3, dx, dy, x0, y0, sx-x0, 0);
								if(t >= 0.0)
								{
									moving_entity.position()->mod_y(-sign(moving_entity.movement()->vy())*(y3-y0));
									//moving_entity->movement()->mod_velocity_y(-sign(moving_entity->movement()->vy())*(y3-y0)/time_diff);
									moving_entity.movement()->set_velocity_y(0);
									if(entity0.id() == moving_entity.id())
									{
										moving_entity.collision()->set_standing_on(Collision::GROUND);
										moving_entity.movement()->mod_force_x(-0.02*dx/time_diff);
									}
								}
								else
								{
									t = lines_cross(x3, y3, dx, dy, sx, y0, 0, sy-y0);
									if(t >= 0.0)
									{
										moving_entity.position()->mod_x(-sign(moving_entity.movement()->vx())*(sx-x3));
										//moving_entity->movement()->mod_velocity_x(-sign(moving_entity->movement()->vx())*(sx-x3)/time_diff);
										moving_entity.movement()->set_velocity_x(0);
									}
									else
									{
										std::cerr << "Error" << std::endl;
									}
								}
							}
						}
					}
				}
        	}
        	else
        	{
        		//error *it0 or *it1
        	}
        }

	std::for_each(cbegin(entities), cend(entities),
	[&](const EntityID id)
	{
		if(entity_system().entity(id))
		{
			const auto it = entity_last_triggered.find(id);
			if(it != cend(entity_last_triggered))
			{
				const Interaction* interaction = entity_system().entity(id)->interaction();
				const bool entity_last_triggered = it->second;
				if(entity_last_triggered > interaction->triggered())
				{	//was triggered, now it is not, so execute on_exit_proc_self
					if(interaction->on_exit_proc_id_self() >= 0)
					{
						command_queue().push(std::make_unique<SelectEntityCommand>(id));
						command_queue().push(std::make_unique<CallProcedureCommand>(interaction->on_exit_proc_id_self()));
					}
				}
				else
				if(entity_last_triggered < interaction->triggered())
				{	//was not triggered, now it is, so execute proc_self
					if(interaction->proc_id_self() >= 0)
					{
						command_queue().push(std::make_unique<SelectEntityCommand>(id));
						command_queue().push(std::make_unique<CallProcedureCommand>(interaction->proc_id_self()));
					}
				}

			}
		}
		else
		{
			//error
		}
	});
}

std::unordered_map<EntityID, bool> CollisionSystem::entities_last_triggered_reset()
{
	std::unordered_map<EntityID, bool> entities_last_triggered;

	std::for_each(cbegin(entities), cend(entities),
	[&](const EntityID id)
	{
		if(entity_system().entity(id))
		{
			Entity& entity = *(entity_system().entity(id));
			entity.collision()->set_standing_on(Collision::AIR);
			entities_last_triggered.insert({id, entity.interaction()->triggered()});
	    	entity.interaction()->set_triggered(false);
		}
		else
		{
			//error
		}
	});

	return entities_last_triggered;
}

