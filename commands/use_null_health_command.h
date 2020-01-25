/*
 * use_null_health_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_NULL_HEALTH_COMMAND_H_
#define COMMANDS_USE_NULL_HEALTH_COMMAND_H_

#include "command.h"

class UseNullHealthCommand : public Command
{
public:
	UseNullHealthCommand() {}
    void execute() const;
    Command* clone() { return new UseNullHealthCommand(); }
};


#endif /* COMMANDS_USE_NULL_HEALTH_COMMAND_H_ */
