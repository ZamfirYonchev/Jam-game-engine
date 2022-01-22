/*
 * clear_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_PROCEDURE_COMMAND_H_
#define COMMANDS_CLEAR_PROCEDURE_COMMAND_H_

#include "../command_value.h"
#include "../types.h"

template<typename CommandSystemT, typename ProcedureResourceSystemT>
class ClearProcedureCommand
{
public:
	CommandSystemT& command_system;
	ProcedureResourceSystemT& procedures;

	ClearProcedureCommand(CommandSystemT& _command_system, ProcedureResourceSystemT& _procedures)
	: command_system{_command_system}
	, procedures{_procedures}
	{}

    CommandValue operator()() const
    {
    	const auto proc_id = command_system.exec_next();
    	auto procedure_opt = procedures[proc_id.integer()];

    	if(procedure_opt)
    		procedure_opt->get().clear();
    	else
    	{
    		//todo add an error
    	}
    	return proc_id;
    }
};


#endif /* COMMANDS_CLEAR_PROCEDURE_COMMAND_H_ */
