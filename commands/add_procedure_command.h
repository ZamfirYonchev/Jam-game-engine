/*
 * add_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_PROCEDURE_COMMAND_H_
#define COMMANDS_ADD_PROCEDURE_COMMAND_H_

#include "command.h"

class AddProcedureCommand : public Command
{
public:
    AddProcedureCommand(int num_of_cmds) : m_num_of_cmds(num_of_cmds) {}
    void execute() const;
    Command* clone() { return new AddProcedureCommand(m_num_of_cmds); }
private:
    int m_num_of_cmds;
};


#endif /* COMMANDS_ADD_PROCEDURE_COMMAND_H_ */
