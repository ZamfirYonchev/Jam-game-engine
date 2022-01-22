/*
 * call_named_procedure_command.h
 *
 *  Created on: Jan 22, 2022
 *      Author: zamfi
 */

#ifndef COMMANDS_CALL_NAMED_PROCEDURE_COMMAND_H_
#define COMMANDS_CALL_NAMED_PROCEDURE_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../types.h"
#include "../utilities.h"
#include <string>
#include "call_fixed_procedure_command.h"

template<typename CommandSystemT, typename ProcedureResourceSystemT>
class CallNamedProcedureCommand
{
public:
	CommandSystemT& command_system;
	ProcedureResourceSystemT& procedures;
	Globals& globals;
	std::string proc_name;

	CallNamedProcedureCommand
	( CommandSystemT& _command_system
	, ProcedureResourceSystemT& _procedures
	, Globals& _globals
	, std::string _proc_name
	)
	: command_system{_command_system}
	, procedures{_procedures}
	, globals{_globals}
	, proc_name{std::move(_proc_name)}
	{}

    CommandValue operator()() const
    {
    	const ProcedureID proc_id = globals(proc_name);
    	return CallFixedProcedureCommand{command_system, procedures, proc_id}();
    }
};

#endif /* COMMANDS_CALL_NAMED_PROCEDURE_COMMAND_H_ */
