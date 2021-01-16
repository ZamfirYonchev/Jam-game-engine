/*
 * procedure_command.h
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_PROCEDURE_COMMAND_H_
#define COMMANDS_PROCEDURE_COMMAND_H_

#include <list>

class ResourceSystem;
class InputSystem;
class RenderingSystem;

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

private:
    std::list<CommandT> m_commands;
};



#endif /* COMMANDS_PROCEDURE_COMMAND_H_ */
