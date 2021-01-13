/*
 * procedure_command.h
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_PROCEDURE_COMMAND_H_
#define COMMANDS_PROCEDURE_COMMAND_H_

#include "command_return_value.h"
#include <list>

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

template<typename CommandSystemT>
class ProcedureCommand
{
public:
	using CommandT = typename CommandSystemT::CommandT;
    void add_command(const CommandT& cmd)
    {
        m_commands.push_back(cmd);
    }

    void clear()
    {
        m_commands.clear();
    }

    std::list<CommandT>& commands()
	{
    	return m_commands;
	}

    void insert_to(CommandSystemT& command_system) const
    {
        for(auto it = m_commands.rbegin(); it != m_commands.rend(); ++it)
        	command_system.insert_front(*it);
    }

    /*template<typename EntitySystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	insert_to(command_system);
        return command_system.exec_next();
    }*/

private:
    std::list<CommandT> m_commands;
};



#endif /* COMMANDS_PROCEDURE_COMMAND_H_ */
