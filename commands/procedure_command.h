/*
 * procedure_command.h
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_PROCEDURE_COMMAND_H_
#define COMMANDS_PROCEDURE_COMMAND_H_

#include "command.h"
#include <list>

class ProcedureCommand : public Command
{
public:
    void add_command(std::unique_ptr<Command> cmd)
    {
        m_commands.push_back(std::move(cmd));
    }

    void clear()
    {
        m_commands.clear();
    }

    void execute() const;
    std::unique_ptr<Command> clone() const
    {
    	auto proc_cmd_ptr = std::make_unique<ProcedureCommand>();
        for(const auto& cmd : m_commands)
        	proc_cmd_ptr->add_command(cmd->clone());
        return proc_cmd_ptr;
    }

private:
    std::list<std::unique_ptr<Command>> m_commands;
};



#endif /* COMMANDS_PROCEDURE_COMMAND_H_ */
