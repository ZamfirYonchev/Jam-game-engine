/*
 * extend_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_EXTEND_PROCEDURE_COMMAND_H_
#define COMMANDS_EXTEND_PROCEDURE_COMMAND_H_

#include "../types.h"
#include "../systems/resource_system.h"
#include "../systems/command_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ExtendProcedureCommand
{
public:
    ExtendProcedureCommand(const AbsProcedureID proc_id, const size_t num_of_commands)
    : m_proc_id(proc_id)
    , m_num_of_cmds(num_of_commands)
    {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
        if(command_system.procedure(m_proc_id))
        {
    		for(size_t i = 0; i < m_num_of_cmds; ++i)
    		{
    			command_system.procedure(m_proc_id)->add_command(command_system.pop_next());
    		}
        }
        else
        {
        	//error m_id
        }
    }

private:
    AbsProcedureID m_proc_id;
    size_t m_num_of_cmds;
};

#endif /* COMMANDS_EXTEND_PROCEDURE_COMMAND_H_ */
