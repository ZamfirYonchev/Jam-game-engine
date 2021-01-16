/*
 * call_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CALL_PROCEDURE_COMMAND_H_
#define COMMANDS_CALL_PROCEDURE_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../types.h"
#include "../utilities.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class CallProcedureCommand
{
public:
	CallProcedureCommand(std::string_view proc_name) : m_procedure{std::string{proc_name}} {}
	CallProcedureCommand(const ProcedureID proc_id) : m_procedure{static_cast<int64_t>(proc_id)} {}
	CallProcedureCommand() : m_procedure{static_cast<int64_t>(0)} {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto proc_id = m_procedure.holds_string() ? globals(m_procedure.string()) :
							(m_procedure.integer() > 0) ? m_procedure
														: command_system.exec_next();

    	if(proc_id.integer() < 0)
    	{
			std::cerr << "CallProcedure: procedure id " << proc_id.integer() << " must be >= 0\n";
			return CommandReturnValue{-1l};
    	}
    	else
    	{
    		command_system.procedure(ProcedureID(proc_id.integer())).insert_to(command_system);
			return command_system.exec_next(); //return the result from the first command
    	}
    }

private:
    const CommandReturnValue m_procedure;
};


#endif /* COMMANDS_CALL_PROCEDURE_COMMAND_H_ */
