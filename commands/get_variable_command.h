/*
 * get_variable_command.h
 *
 *  Created on: Jan 11, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_GET_VARIABLE_COMMAND_H_
#define COMMANDS_GET_VARIABLE_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../utilities.h"

template<typename CommandSystemT>
class GetVariableCommand
{
public:
	CommandSystemT& command_system;
	Globals& globals;

	GetVariableCommand(CommandSystemT& _command_system, Globals& _globals)
	: command_system{_command_system}
	, globals{_globals}
	{}

    CommandValue operator()() const
	{
		const auto name = command_system.exec_next();
		return globals(name.string());
	}
};

#endif /* COMMANDS_GET_VARIABLE_COMMAND_H_ */
