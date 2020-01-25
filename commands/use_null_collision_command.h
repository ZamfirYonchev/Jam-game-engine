/*
 * use_null_collision_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_NULL_COLLISION_COMMAND_H_
#define COMMANDS_USE_NULL_COLLISION_COMMAND_H_

#include "command.h"

class UseNullCollisionCommand : public Command
{
public:
	UseNullCollisionCommand() {}
    void execute() const;
    Command* clone() { return new UseNullCollisionCommand(); }
};

#endif /* COMMANDS_USE_NULL_COLLISION_COMMAND_H_ */
