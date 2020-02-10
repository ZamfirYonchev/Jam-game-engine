/*
 * use_null_movement_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_NULL_MOVEMENT_COMMAND_H_
#define COMMANDS_USE_NULL_MOVEMENT_COMMAND_H_

#include "command.h"

class UseNullMovementCommand : public Command
{
public:
	UseNullMovementCommand() {}
    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseNullMovementCommand>(); }
};


#endif /* COMMANDS_USE_NULL_MOVEMENT_COMMAND_H_ */
