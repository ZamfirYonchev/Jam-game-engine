/*
 * set_fixed_variable_command.h
 *
 *  Created on: Dec 10, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_SET_FIXED_VARIABLE_COMMAND_H_
#define COMMANDS_SET_FIXED_VARIABLE_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../utilities.h"

template<typename CommandSystemT>
class SetFixedVariableCommand
{
public:
	CommandSystemT& command_system;
	Globals& globals;

	SetFixedVariableCommand(CommandSystemT& _command_system, Globals& _globals, const HashT name_hash)
	: command_system{_command_system}
	, globals{_globals}
	, m_hash{name_hash}
	{}

    CommandValue operator()() const
	{
    	const auto result = command_system.exec_next();
    	globals(m_hash) = result;
    	return result;
	}

private:
    HashT m_hash;
};

#endif /* COMMANDS_SET_FIXED_VARIABLE_COMMAND_H_ */
