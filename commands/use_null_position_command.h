/*
 * use_null_position_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_NULL_POSITION_COMMAND_H_
#define COMMANDS_USE_NULL_POSITION_COMMAND_H_

#include "command.h"

class UseNullPositionCommand : public Command
{
public:
	UseNullPositionCommand() {}
    void execute() const;
    Command* clone() { return new UseNullPositionCommand(); }
};

#endif /* COMMANDS_USE_NULL_POSITION_COMMAND_H_ */
