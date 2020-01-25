/*
 * clear_all_procedures_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_
#define COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_

#include "command.h"

class ClearAllProceduresCommand : public Command
{
public:
    ClearAllProceduresCommand() {}
    void execute() const;
    Command* clone() { return new ClearAllProceduresCommand(); }
};

#endif /* COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_ */
