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
    ~ProcedureCommand()
    {
        for(auto it = m_commands.begin(); it != m_commands.end(); ++it)
            delete *it;
    }

    void add_command(Command* cmd)
    {
        m_commands.push_back(cmd);
    }

    void clear()
    {
        for(auto it = m_commands.begin(); it != m_commands.end(); ++it)
            delete *it;
        m_commands.clear();
    }

    void execute() const;
    Command* clone()
    {
        ProcedureCommand* cmd = new ProcedureCommand();
        for(auto it = m_commands.begin(); it != m_commands.end(); ++it)
            cmd->add_command((*it)->clone());
        return cmd;
    }

private:
    std::list<Command*> m_commands;
};



#endif /* COMMANDS_PROCEDURE_COMMAND_H_ */
