/*
 * procedure.h
 *
 *  Created on: Dec 17, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_PROCEDURE_H_
#define COMMANDS_PROCEDURE_H_

#include <vector>

template<typename CommandSystemT>
class Procedure
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

    std::vector<CommandT>& commands()
	{
    	return m_commands;
	}

    void insert_to(CommandSystemT& command_system) const
    {
        for(auto it = m_commands.rbegin(); it != m_commands.rend(); ++it)
        	command_system.insert_front(*it);
    }

private:
    std::vector<CommandT> m_commands;
};

#endif /* COMMANDS_PROCEDURE_H_ */
