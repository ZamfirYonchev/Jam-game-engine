/*
 * extend_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_EXTEND_PROCEDURE_COMMAND_H_
#define COMMANDS_EXTEND_PROCEDURE_COMMAND_H_

#include "command.h"
#include "../types.h"

class ExtendProcedureCommand : public Command
{
public:
    ExtendProcedureCommand(ProcedureID id, int num_of_commands)
    : m_id(id)
    , m_num_of_cmds(num_of_commands)
    {}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<ExtendProcedureCommand>(m_id, m_num_of_cmds); }

private:
    ProcedureID m_id;
    int m_num_of_cmds;
};

#endif /* COMMANDS_EXTEND_PROCEDURE_COMMAND_H_ */
