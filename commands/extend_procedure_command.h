/*
 * extend_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_EXTEND_PROCEDURE_COMMAND_H_
#define COMMANDS_EXTEND_PROCEDURE_COMMAND_H_

#include "../types.h"

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
    			const auto& cmd_optional = command_system.pop_next();
    			if(cmd_optional)
    				command_system.procedure(m_proc_id)->add_command(*cmd_optional);
    			else
    				std::cerr << "Trying to extend procedure " << m_proc_id << " from an empty queue." << '\n';
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
