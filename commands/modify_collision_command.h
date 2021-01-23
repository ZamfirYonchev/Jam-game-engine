/*
 * modify_collision_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_COLLISION_COMMAND_H_
#define COMMANDS_MODIFY_COLLISION_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../math_ext.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class ModifyCollisionCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto state = command_system.exec_next();
    	const auto standing_on = command_system.exec_next();
    	const auto on_collision_damage = command_system.exec_next();
    	const auto elasticity = command_system.exec_next();

    	const EntityID selected_entity = globals(Globals::selected_entity).integer();
    	Collision& collision = entity_system.entity_component(selected_entity, Collision::null);

		if(collision)
		{
			if(is_negative_zero(state.real()))
				collision.set_state(Collision::CollisionState(0));
			else
				collision.set_state(Collision::CollisionState((state.integer() + int(collision.state()))%3));

			if(is_negative_zero(standing_on.real()))
				collision.set_standing_on(Collision::SurfaceType::AIR);
			else
				collision.set_standing_on(Collision::SurfaceType((standing_on.integer() + int(collision.standing_on()))%4));

			if(is_negative_zero(on_collision_damage.real()))
				collision.set_collision_damage(0);
			else
				collision.set_collision_damage(collision.on_collision_damage() + on_collision_damage.real());

			if(is_negative_zero(elasticity.real()))
				collision.set_elasticity(0);
			else
				collision.set_elasticity(clip(collision.elasticity() + elasticity.real(), 0.0, 1.0));

			return CommandReturnValue{0.0};
		}
		else
		{
			//error selected_entity
			return CommandReturnValue{-1l};
		}
	}
};

#endif /* COMMANDS_MODIFY_COLLISION_COMMAND_H_ */
