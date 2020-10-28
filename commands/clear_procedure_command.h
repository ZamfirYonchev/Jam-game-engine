/*
 * clear_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_PROCEDURE_COMMAND_H_
#define COMMANDS_CLEAR_PROCEDURE_COMMAND_H_

#include "../types.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ClearProcedureCommand
{
public:
    ClearProcedureCommand(const ProcedureID proc_id) : m_proc_id(proc_id) {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	if(command_system.procedure(m_proc_id))
    	{
    		command_system.procedure(m_proc_id)->clear();
    	}
    	else
    	{
    		//error m_id
    	}
    }

private:
    ProcedureID m_proc_id;
};


#endif /* COMMANDS_CLEAR_PROCEDURE_COMMAND_H_ */
