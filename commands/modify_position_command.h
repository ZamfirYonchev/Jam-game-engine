/*
 * modify_position_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_POSITION_COMMAND_H_
#define COMMANDS_MODIFY_POSITION_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../math_ext.h"
#include "../components/position.h"

template<typename CommandSystemT, typename EntitySystemT, typename PositionT>
class ModifyPositionCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;
	Globals& globals;

	ModifyPositionCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system, Globals& _globals)
	: command_system{_command_system}
	, entity_system{_entity_system}
	, globals{_globals}
	{}

	CommandValue operator()() const
	{
    	const auto x = command_system.exec_next();
    	const auto y = command_system.exec_next();
    	const auto w = command_system.exec_next();
    	const auto h = command_system.exec_next();

    	const EntityID selected_entity = globals(Globals::selected_entity);
    	auto& position = entity_system.template entity_component<PositionT>(selected_entity);

		if(position)
		{
			if(is_negative_zero(x.real()))
				position.set_x(0.0);
			else
				position.mod_x(x.real());

			if(is_negative_zero(y.real()))
				position.set_y(0.0);
			else
				position.mod_y(y.real());

			if(is_negative_zero(w.real()))
				position.set_w(0.0);
			else
				position.mod_w(w.real());

			if(is_negative_zero(h.real()))
				position.set_h(0.0);
			else
				position.mod_h(h.real());

			return globals(Globals::selected_entity);
		}
		else
		{
			//error selected_entity
			return CommandValue{-1};
		}
	}
};


#endif /* COMMANDS_MODIFY_POSITION_COMMAND_H_ */
