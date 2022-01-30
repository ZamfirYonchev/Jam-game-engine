/*
 * increment_variable_command.h
 *
 *  Created on: Jan 28, 2022
 *      Author: zamfi
 */

#ifndef COMMANDS_INCREMENT_VARIABLE_COMMAND_H_
#define COMMANDS_INCREMENT_VARIABLE_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../utilities.h"

template<typename CommandSystemT>
class IncrementVariableCommand
{
public:
	CommandSystemT& command_system;
	Globals& globals;

	IncrementVariableCommand(CommandSystemT& _command_system, Globals& _globals)
	: command_system{_command_system}
	, globals{_globals}
	{}

    CommandValue operator()() const
	{
		const std::string name = command_system.exec_next();
		const double increment_value = command_system.exec_next();
		const HashT name_hash = hash(name.data());

		const auto result = CommandValue{ globals(name_hash).real() + increment_value };
    	globals(name_hash) = result;

    	return result;
	}
};




#endif /* COMMANDS_INCREMENT_VARIABLE_COMMAND_H_ */
