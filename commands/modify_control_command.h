/*
 * modify_control_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_CONTROL_COMMAND_H_
#define COMMANDS_MODIFY_CONTROL_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../math_ext.h"

template<typename CommandSystemT, typename EntitySystemT, typename ControlT>
class ModifyControlCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;
	Globals& globals;

	ModifyControlCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system, Globals& _globals)
	: command_system{_command_system}
	, entity_system{_entity_system}
	, globals{_globals}
	{}

	CommandValue operator()() const
	{
    	const auto decision_vertical = command_system.exec_next();
    	const auto decision_attack = command_system.exec_next();
    	const auto decision_walk = command_system.exec_next();
    	const auto look_dir = command_system.exec_next();

    	const EntityID selected_entity = globals(Globals::selected_entity);
    	auto& control = entity_system.template entity_component<ControlT>(selected_entity);

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

			return globals(Globals::selected_entity);
		}
		else
		{
			//error selected_entity
			return CommandValue{-1};
		}
	}
};


#endif /* COMMANDS_MODIFY_CONTROL_COMMAND_H_ */
