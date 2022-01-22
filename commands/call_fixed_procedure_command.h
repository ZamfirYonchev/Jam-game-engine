/*
 * call_fixed_procedure_command.h
 *
 *  Created on: Jan 21, 2022
 *      Author: zamfi
 */

#ifndef COMMANDS_CALL_FIXED_PROCEDURE_COMMAND_H_
#define COMMANDS_CALL_FIXED_PROCEDURE_COMMAND_H_

#include "../command_value.h"
#include "../types.h"

template<typename CommandSystemT, typename ProcedureResourceSystemT>
class CallFixedProcedureCommand
{
public:
	CommandSystemT& command_system;
	ProcedureResourceSystemT& procedures;
    ProcedureID proc_id;

	CallFixedProcedureCommand
	( CommandSystemT& _command_system
	, ProcedureResourceSystemT& _procedures
	, const ProcedureID _proc_id
	)
	: command_system{_command_system}
	, procedures{_procedures}
	, proc_id{_proc_id}
	{}

    CommandValue operator()() const
    {
		const auto procedure_opt = procedures[proc_id];

		if(procedure_opt)
		{
			command_system.insert(procedure_opt->get());
			return command_system.exec_next(); //return the result from the first command
		}
		else
		{
			//TODO error
			return CommandValue{-1};
		}
    }
};




#endif /* COMMANDS_CALL_FIXED_PROCEDURE_COMMAND_H_ */
