/*
 * clear_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_PROCEDURE_COMMAND_H_
#define COMMANDS_CLEAR_PROCEDURE_COMMAND_H_

#include "command.h"
#include "../types.h"

class ClearProcedureCommand : public Command
{
public:
    ClearProcedureCommand(ProcedureID id) : m_id(id) {}
    void execute() const;
    Command* clone() { return new ClearProcedureCommand(m_id); }

private:
    ProcedureID m_id;
};


#endif /* COMMANDS_CLEAR_PROCEDURE_COMMAND_H_ */
