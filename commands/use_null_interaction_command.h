/*
 * use_null_interaction_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_NULL_INTERACTION_COMMAND_H_
#define COMMANDS_USE_NULL_INTERACTION_COMMAND_H_

#include "command.h"

class UseNullInteractionCommand : public Command
{
public:
	UseNullInteractionCommand() {}

    void execute() const;
	std::unique_ptr<Command> clone() { return std::make_unique<UseNullInteractionCommand>(); }
};


#endif /* COMMANDS_USE_NULL_INTERACTION_COMMAND_H_ */
