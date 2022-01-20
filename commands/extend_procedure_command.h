/*
 * extend_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_EXTEND_PROCEDURE_COMMAND_H_
#define COMMANDS_EXTEND_PROCEDURE_COMMAND_H_

#include "../command_value.h"
#include "../types.h"

template<typename CommandSystemT>
class ExtendProcedureCommand
{
public:
	CommandSystemT& command_system;
	ExtendProcedureCommand(CommandSystemT& _command_system)
	: command_system{_command_system}
	{}

    CommandValue operator()() const
    {
    	const auto proc_id = command_system.exec_next();
    	const int num_of_cmds = command_system.exec_next();

    	auto& proc = command_system.procedure(ProcedureID(proc_id.integer()));

		for(int i = 0; i < num_of_cmds; ++i)
		{
			proc.add_command(command_system.pop_next());
		}

		return proc_id;
    }
};

#endif /* COMMANDS_EXTEND_PROCEDURE_COMMAND_H_ */
