/*
 * call_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CALL_PROCEDURE_COMMAND_H_
#define COMMANDS_CALL_PROCEDURE_COMMAND_H_

#include "../types.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class CallProcedureCommand
{
public:
    CallProcedureCommand(const AbsProcedureID proc_id) : m_proc_id(proc_id) {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	if(command_system.procedure(m_proc_id))
    		(*command_system.procedure(m_proc_id))(entity_system, resource_system, input_system, command_system, rendering_system, all_systems, globals);
    	else
    	{
    		//error m_id
    	}
    }

private:
    AbsProcedureID m_proc_id;
};


#endif /* COMMANDS_CALL_PROCEDURE_COMMAND_H_ */
