/*
 * get_fixed_variable_command.h
 *
 *  Created on: Dec 10, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_GET_FIXED_VARIABLE_COMMAND_H_
#define COMMANDS_GET_FIXED_VARIABLE_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../utilities.h"

template<typename CommandSystemT>
class GetFixedVariableCommand
{
public:
	CommandSystemT& command_system;
	Globals& globals;

	GetFixedVariableCommand(CommandSystemT& _command_system, Globals& _globals, std::string_view name)
	: command_system{_command_system}
	, globals{_globals}
	, m_hash{hash(name.data())} {}

    CommandValue operator()() const
	{
		return globals(m_hash);
	}

private:
    HashT m_hash;
};

#endif /* COMMANDS_GET_FIXED_VARIABLE_COMMAND_H_ */
