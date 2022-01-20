/*
 * clear_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_PROCEDURE_COMMAND_H_
#define COMMANDS_CLEAR_PROCEDURE_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../types.h"

template<typename CommandSystemT>
class ClearProcedureCommand
{
public:
	CommandSystemT& command_system;

	ClearProcedureCommand(CommandSystemT& _command_system)
	: command_system{_command_system}
	{}

    CommandValue operator()() const
    {
    	const auto proc_id = command_system.exec_next();
    	command_system.procedure(proc_id.integer()).clear();
    	return proc_id;
    }
};


#endif /* COMMANDS_CLEAR_PROCEDURE_COMMAND_H_ */
