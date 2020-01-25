/*
 * call_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CALL_PROCEDURE_COMMAND_H_
#define COMMANDS_CALL_PROCEDURE_COMMAND_H_

#include "command.h"
#include "../types.h"

class CallProcedureCommand : public Command
{
public:
    CallProcedureCommand(ProcedureID id)
    : m_id(id)
    {}

    void execute() const;
    Command* clone() { return new CallProcedureCommand(m_id); }

private:
    ProcedureID m_id;
};


#endif /* COMMANDS_CALL_PROCEDURE_COMMAND_H_ */
