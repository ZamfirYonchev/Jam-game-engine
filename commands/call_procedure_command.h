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

template<typename CommandSystemT>
class CallProcedureCommand
{
public:
	CommandSystemT& command_system;
	Globals& globals;
    const CommandValue m_procedure;

	CallProcedureCommand(CommandSystemT& _command_system, Globals& _globals, std::string_view proc_name)
	: command_system{_command_system}
	, globals{_globals}
	, m_procedure{std::string{proc_name}}
	{}

	CallProcedureCommand(CommandSystemT& _command_system, Globals& _globals, const ProcedureID proc_id)
	: command_system{_command_system}
	, globals{_globals}
	, m_procedure{proc_id, 0} {} // @suppress("Symbol is not resolved")

	CallProcedureCommand(CommandSystemT& _command_system, Globals& _globals)
	: command_system{_command_system}
	, globals{_globals}
	, m_procedure{0.0} {}

    CommandValue operator()() const
    {
    	const auto proc_id = m_procedure.holds_string() ? globals(m_procedure.string()) :
							(m_procedure.integer() > 0) ? m_procedure
														: command_system.exec_next();

    	if(proc_id.integer() < 0)
    	{
			std::cerr << "CallProcedure: procedure id " << proc_id.integer() << " must be >= 0\n";
			return CommandValue{-1};
    	}
    	else
    	{
    		command_system.procedure(ProcedureID(proc_id.integer())).insert_to(command_system);
			return command_system.exec_next(); //return the result from the first command
    	}
    }
};


#endif /* COMMANDS_CALL_PROCEDURE_COMMAND_H_ */
