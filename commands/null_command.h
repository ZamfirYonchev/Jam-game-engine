/*
 * null_command.h
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_NULL_COMMAND_H_
#define COMMANDS_NULL_COMMAND_H_

#include "command.h"

class NullCommand : public Command
{
public:
    void execute() const {}
    Command* clone() { return new NullCommand(); }
};

#endif /* COMMANDS_NULL_COMMAND_H_ */
