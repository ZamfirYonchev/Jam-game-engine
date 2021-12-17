/*
 * clear_all_procedures_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_
#define COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"

template<typename CommandSystemT>
class ClearAllProceduresCommand
{
public:
	CommandSystemT& command_system;

    ClearAllProceduresCommand(CommandSystemT& _command_system) : command_system{_command_system} {}

    CommandValue operator()() const
    {
    	command_system.clear_procedures();
    	return CommandValue{0};
    }
};

#endif /* COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_ */
