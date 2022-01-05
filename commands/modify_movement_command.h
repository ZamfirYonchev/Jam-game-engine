/*
 * modify_movement_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_MOVEMENT_COMMAND_H_
#define COMMANDS_MODIFY_MOVEMENT_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../math_ext.h"

template<typename CommandSystemT, typename EntitySystemT, typename MovementT>
class ModifyMovementCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;
	Globals& globals;

	ModifyMovementCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system, Globals& _globals)
	: command_system{_command_system}
	, entity_system{_entity_system}
	, globals{_globals}
	{}

	CommandValue operator()() const
	{
    	const auto mass = command_system.exec_next();
    	const auto friction_x = command_system.exec_next();
    	const auto friction_y = command_system.exec_next();
    	const auto vx = command_system.exec_next();
    	const auto vy = command_system.exec_next();
    	const auto fx = command_system.exec_next();
    	const auto fy = command_system.exec_next();
    	const auto gravity_affected = command_system.exec_next();

    	const EntityID selected_entity = globals(Globals::selected_entity).integer();
    	auto& movement = entity_system.template entity_component<MovementT>(selected_entity);

		if(movement)
		{
			if(is_negative_zero(mass.real()))
				movement.set_mass(mass.real());
			else
				movement.set_mass(movement.mass() + mass.real());

			if(is_negative_zero(friction_x.real()))
				movement.set_friction_x(0.0);
			else
				movement.set_friction_x(movement.friction_x() + friction_x.real());

			if(is_negative_zero(friction_y.real()))
				movement.set_friction_y(0.0);
			else
				movement.set_friction_y(movement.friction_y() + friction_y.real());

			if(is_negative_zero(fx.real()))
				movement.set_force_x(0.0);
			else
				movement.mod_force_x(fx.real());

			if(is_negative_zero(fy.real()))
				movement.set_force_y(0.0);
			else
				movement.mod_force_y(fy.real());

			if(is_negative_zero(vx.real()))
				movement.set_velocity_x(0.0);
			else
				movement.mod_velocity_x(vx.real());

			if(is_negative_zero(vy.real()))
				movement.set_velocity_y(0.0);
			else
				movement.mod_velocity_y(vy.real());

			if(is_negative_zero(gravity_affected.real()))
				movement.set_gravity_affected(false);
			else
				movement.set_gravity_affected(gravity_affected.boolean() ^ movement.gravity_affected());

			return globals(Globals::selected_entity);
		}
		else
		{
			//error selected_entity
			return CommandValue{-1};
		}
	}
};


#endif /* COMMANDS_MODIFY_MOVEMENT_COMMAND_H_ */
