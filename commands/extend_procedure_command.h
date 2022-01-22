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

template<typename CommandSystemT, typename ProcedureResourceSystemT>
class ExtendProcedureCommand
{
public:
	CommandSystemT& command_system;
	ProcedureResourceSystemT& procedures;

	ExtendProcedureCommand(CommandSystemT& _command_system, ProcedureResourceSystemT& _procedures)
	: command_system{_command_system}
	, procedures{_procedures}
	{}

    CommandValue operator()() const
    {
    	const auto proc_id = command_system.exec_next();
    	const int num_of_cmds = command_system.exec_next();

    	auto proc_opt = procedures[ProcedureID(proc_id.integer())];

    	if(proc_opt)
    	{
			for(int i = 0; i < num_of_cmds; ++i)
			{
				proc_opt->get().push_back(command_system.pop_next());
			}
    	}
    	else
    	{
    		//TODO error
    	}

		return proc_id;
    }
};

#endif /* COMMANDS_EXTEND_PROCEDURE_COMMAND_H_ */
