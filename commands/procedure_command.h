/*
 * procedure_command.h
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_PROCEDURE_COMMAND_H_
#define COMMANDS_PROCEDURE_COMMAND_H_

#include <list>
#include "../systems/command_system.h"

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

    template<typename EntitySystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
        for(auto it = m_commands.rbegin(); it != m_commands.rend(); ++it)
        	command_system.insert_next(*it);
    }

private:
    std::list<CommandT> m_commands;
};



#endif /* COMMANDS_PROCEDURE_COMMAND_H_ */
