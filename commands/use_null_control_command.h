/*
 * use_null_control_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_NULL_CONTROL_COMMAND_H_
#define COMMANDS_USE_NULL_CONTROL_COMMAND_H_

#include "command.h"

class UseNullControlCommand : public Command
{
public:
	UseNullControlCommand() {}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseNullControlCommand>(); }
};

#endif /* COMMANDS_USE_NULL_CONTROL_COMMAND_H_ */
