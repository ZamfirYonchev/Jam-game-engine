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
#include <limits>

struct CorrectionValues
{
	CorrectionValues() : x{0}, y{0}, vx{0}, vy{0} {}
	double x, y, vx, vy;
};

void CollisionSystem::add_id(const EntityID entity_id)
{
	SystemBase::add_id(entity_id);

	const auto entity_optional = entity_system().entity(entity_id);
	if(entity_optional)
	{
		const Entity& entity = *entity_optional;
		const int start_region_x = std::floor(entity.position()->x() / REGION_W);
		const int start_region_y = std::floor(entity.position()->y() / REGION_H);
		const int end_region_x = std::ceil((entity.position()->x()+entity.position()->w()) / REGION_W);
		const int end_region_y = std::ceil((entity.position()->y()+entity.position()->h()) / REGION_H);

		for(int region_x = start_region_x; region_x < end_region_x; ++region_x)
			for(int region_y = start_region_y; region_y < end_region_y; ++region_y)
			{
				const RegionPosition region_pos = {region_x, region_y};
				entity_regions[region_pos].insert(entity_id);
				//std::cout << "Adding id " << entity_id << " to region[" << region_pos.x << ", " << region_pos.y << "]" << std::endl;
			}
	}
	else
	{
		//error entity_id
	}
}

void CollisionSystem::remove_id(const EntityID entity_id)
{
	SystemBase::remove_id(entity_id);

	const auto& entity_optional = entity_system().entity(entity_id);
	if(entity_optional)
	{
		const Entity& entity = *entity_optional;
		const int start_region_x = std::floor(entity.position()->x() / REGION_W);
		const int start_region_y = std::floor(entity.position()->y() / REGION_H);
		const int end_region_x = std::ceil((entity.position()->x()+entity.position()->w()) / REGION_W);
		const int end_region_y = std::ceil((entity.position()->y()+entity.position()->h()) / REGION_H);

		for(int region_x = start_region_x; region_x < end_region_x; ++region_x)
			for(int region_y = start_region_y; region_y < end_region_y; ++region_y)
			{
				const RegionPosition region_pos = {region_x, region_y};
				entity_regions[region_pos].erase(entity_id);
			}
	}
	else
	{
		//error entity_id
	}
}

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
		const auto entity_optional = entity_system().entity(entity_id);
		if(entity_optional)
		{
			const Entity& entity = *entity_optional;
			if(entity_optional->movement()->dx() != 0 || entity_optional->movement()->dy() != 0)
			{
				const RegionPosition new_start_region {int(std::floor(entity.position()->x() / REGION_W)), int(std::floor(entity.position()->y() / REGION_H))};
				const RegionPosition old_start_region {int(std::floor((entity.position()->x()-entity.movement()->dx()) / REGION_W)), int(std::floor((entity.position()->y()-entity.movement()->dy()) / REGION_H))};

				if(old_start_region != new_start_region)
				{
					const RegionPosition new_end_region = {int(std::ceil((entity.position()->x()+entity.position()->w()) / REGION_W)), int(std::ceil((entity.position()->y()+entity.position()->h()) / REGION_H))};
					const RegionPosition old_end_region = {int(std::ceil((entity.position()->x()+entity.position()->w()-entity.movement()->dx()) / REGION_W)), int(std::ceil((entity.position()->y()+entity.position()->h()-entity.movement()->dy()) / REGION_H))};

					for(int region_x = old_start_region.x; region_x <= old_end_region.x; ++region_x)
						for(int region_y = old_start_region.y; region_y <= old_end_region.y; ++region_y)
							entity_regions[RegionPosition{region_x, region_y}].erase(entity_id);

					for(int region_x = new_start_region.x; region_x <= new_end_region.x; ++region_x)
						for(int region_y = new_start_region.y; region_y <= new_end_region.y; ++region_y)
							entity_regions[RegionPosition{region_x, region_y}].insert(entity_id);
				}
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
			entity0.collision()->set_standing_on(Collision::AIR);

			const int start_region_x = std::floor(entity0.position()->x() / REGION_W);
			const int start_region_y = std::floor(entity0.position()->y() / REGION_H);
			const int end_region_x = std::ceil((entity0.position()->x()+entity0.position()->w()) / REGION_W);
			const int end_region_y = std::ceil((entity0.position()->y()+entity0.position()->h()) / REGION_H);

			if(entity0.id() == 27)
				std::cout << "Entity 27 " << "[" << entity0.position()->x() << ", " << entity0.position()->y() << "] regions start at " << start_region_x << ", " << start_region_y << " and ends at " << end_region_x << ", " << end_region_y << '\n';
			std::set<EntityID> near_entities;

			const double x1 = entity0.position()->x() + entity0.position()->w();
			const double y1 = entity0.position()->y() + entity0.position()->h();

			for(int region_x = start_region_x; region_x < end_region_x; ++region_x)
				for(int region_y = start_region_y; region_y < end_region_y; ++region_y)
				{
					const RegionPosition current_region {region_x, region_y};
					for(auto entity_id : entity_regions[current_region])
						near_entities.insert(entity_id);
				}
			near_entities.erase(*it0); //remove self from the set

			for(auto it1 = cbegin(near_entities); it1 != cend(near_entities); ++it1)
			{
				const auto entity1_optional = entity_system().entity(*it1);
				if(entity1_optional && entity1_optional->id() != entity0.id())
				{
					const Entity& entity1 = *entity1_optional;
					Collision* collision0 = entity0.collision();
					const Collision* collision1 = entity1.collision();

					if(objects_collide(entity0.position()->x(), entity0.position()->y(), entity0.position()->w(), entity0.position()->h()
									 , entity1.position()->x(), entity1.position()->y(), entity1.position()->w(), entity1.position()->h()
									  )
					  )
					{
						//entities collide
						Interaction* interaction0 = entity0.interaction();
						const Interaction* interaction1 = entity1.interaction();

						interaction0->set_triggered_groups(interaction1->group_vector());
						//interaction1->set_triggered_groups(interaction0->group_vector());

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

						if(entity0.id() == 2 && entity1.id() == 26)
							std::cout << "colliding with id " << entity1.id() << '\n';
						entity0.health()->mod_hp_change(-collision1->on_collision_damage()*time_diff);
						//entity1.health()->mod_hp_change(-collision0->on_collision_damage()*time_diff);

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
									entity0.collision()->set_standing_on(Collision::GROUND);
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
			const int32_t last_triggered_groups = interaction->last_triggered_groups();
			const int32_t triggered_groups = interaction->triggered_groups();
			const int32_t trigger_group_mask = 1 << interaction->trigger_group();
			const bool trigger_valid = ((last_triggered_groups ^ triggered_groups) & trigger_group_mask) != 0;
			if(trigger_valid)
			{
				const bool triggered = (triggered_groups & trigger_group_mask) != 0;

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
