/*
 * call_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CALL_PROCEDURE_COMMAND_H_
#define COMMANDS_CALL_PROCEDURE_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../types.h"
#include "../utilities.h"
#include "call_fixed_procedure_command.h"

template<typename CommandSystemT, typename ProcedureResourceSystemT>
class CallProcedureCommand
{
public:
	CommandSystemT& command_system;
	ProcedureResourceSystemT& procedures;
	Globals& globals;
    const CommandValue m_procedure;

	CallProcedureCommand
	( CommandSystemT& _command_system
	, ProcedureResourceSystemT& _procedures
	, Globals& _globals
	)
	: command_system{_command_system}
	, procedures{_procedures}
	, globals{_globals}
	, m_procedure{0.0} {}

    CommandValue operator()() const
    {
    	const ProcedureID proc_id = command_system.exec_next();

    	return CallFixedProcedureCommand{command_system, procedures, proc_id}();
    }
};


#endif /* COMMANDS_CALL_PROCEDURE_COMMAND_H_ */
