/*
 * modify_control_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_CONTROL_COMMAND_H_
#define COMMANDS_MODIFY_CONTROL_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../math_ext.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class ModifyControlCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto decision_vertical = command_system.exec_next();
    	const auto decision_attack = command_system.exec_next();
    	const auto decision_walk = command_system.exec_next();
    	const auto look_dir = command_system.exec_next();

    	const EntityID selected_entity = globals(Globals::selected_entity).integer();
    	Control& control = entity_system.template entity_component<Control>(selected_entity);

		if(control)
		{
			if(is_negative_zero(decision_vertical.real()))
				control.set_decision_vertical(0);
			else
				control.mod_decision_vertical(decision_vertical.real());

			if(is_negative_zero(decision_attack.real()))
				control.set_decision_attack(false);
			else
				control.set_decision_attack(decision_attack.boolean() ^ control.decision_attack());

			if(is_negative_zero(decision_walk.real()))
				control.set_decision_walk(0);
			else
				control.mod_decision_walk(decision_walk.real());

			if(is_negative_zero(look_dir.real()))
				control.set_look_dir(Control::LookDir::RIGHT);
			else
				control.set_look_dir(Control::LookDir(look_dir.boolean() ^ bool(control.look_dir())));

			return CommandReturnValue{0.0};
		}
		else
		{
			//error selected_entity
			return CommandReturnValue{-1.0};
		}
	}
};


#endif /* COMMANDS_MODIFY_CONTROL_COMMAND_H_ */
