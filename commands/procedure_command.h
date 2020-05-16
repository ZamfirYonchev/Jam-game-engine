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
	ProcedureCommand() {}
	ProcedureCommand(const ProcedureCommand& rhs) = default;
	ProcedureCommand(ProcedureCommand&& rhs) = default;
	~ProcedureCommand() = default;

    void add_command(std::unique_ptr<Command> cmd)
    {
        m_commands.push_back(std::move(cmd));
    }

    void clear()
    {
        m_commands.clear();
    }

    void execute() const;
    std::unique_ptr<Command> clone()
    {
        ProcedureCommand cmd = ProcedureCommand();
        for(auto it = m_commands.begin(); it != m_commands.end(); ++it)
            cmd.add_command((*it)->clone());
        return std::make_unique<ProcedureCommand>(std::move(cmd));
    }

private:
    std::list<std::unique_ptr<Command>> m_commands;
};



#endif /* COMMANDS_PROCEDURE_COMMAND_H_ */
