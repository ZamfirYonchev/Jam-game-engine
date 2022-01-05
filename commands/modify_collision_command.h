/*
 * modify_collision_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_COLLISION_COMMAND_H_
#define COMMANDS_MODIFY_COLLISION_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../math_ext.h"

template<typename CommandSystemT, typename EntitySystemT, typename CollisionT>
class ModifyCollisionCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;
	Globals& globals;

	ModifyCollisionCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system, Globals& _globals)
	: command_system{_command_system}
	, entity_system{_entity_system}
	, globals{_globals}
	{}

	CommandValue operator()() const
	{
    	const auto solid = command_system.exec_next();
    	const auto standing_on = command_system.exec_next();
    	const auto on_collision_damage = command_system.exec_next();
    	const auto elasticity = command_system.exec_next();

    	const EntityID selected_entity = globals(Globals::selected_entity).integer();
    	auto& collision = entity_system.template entity_component<CollisionT>(selected_entity);

		if(collision)
		{
			if(is_negative_zero(solid.real()))
				collision.set_solid(false);
			else
				collision.set_solid(solid.boolean() ^ collision.solid());

			if(is_negative_zero(standing_on.real()))
				collision.set_standing_on(SurfaceType::AIR);
			else
				collision.set_standing_on(SurfaceType((standing_on.integer() + int(collision.standing_on()))%4));

			if(is_negative_zero(on_collision_damage.real()))
				collision.set_collision_damage(0);
			else
				collision.set_collision_damage(collision.on_collision_damage() + on_collision_damage.real());

			if(is_negative_zero(elasticity.real()))
				collision.set_elasticity(0);
			else
				collision.set_elasticity(clip(collision.elasticity() + elasticity.real(), 0.0, 1.0));

			return globals(Globals::selected_entity);
		}
		else
		{
			//error selected_entity
			return CommandValue{-1};
		}
	}
};

#endif /* COMMANDS_MODIFY_COLLISION_COMMAND_H_ */
