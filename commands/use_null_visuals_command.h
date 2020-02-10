/*
 * use_null_visuals_command.h
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_NULL_VISUALS_COMMAND_H_
#define COMMANDS_USE_NULL_VISUALS_COMMAND_H_

#include "command.h"

class UseNullVisualsCommand : public Command
{
public:
	UseNullVisualsCommand() {}
    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseNullVisualsCommand>(); }
};

#endif /* COMMANDS_USE_NULL_VISUALS_COMMAND_H_ */
