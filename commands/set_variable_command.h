/*
 * set_variable_command.h
 *
 *  Created on: Dec 28, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_SET_VARIABLE_COMMAND_H_
#define COMMANDS_SET_VARIABLE_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../utilities.h"

template<typename CommandSystemT>
class SetVariableCommand
{
public:
	CommandSystemT& command_system;
	Globals& globals;

	SetVariableCommand(CommandSystemT& _command_system, Globals& _globals)
	: command_system{_command_system}
	, globals{_globals}
	{}

    CommandValue operator()() const
	{
		const std::string name = command_system.exec_next();
		const HashT name_hash = hash(name.data());

    	const auto result = command_system.exec_next();
    	globals(name_hash) = result;

    	return result;
	}
};

#endif /* COMMANDS_SET_VARIABLE_COMMAND_H_ */
