/*
 * clear_all_entities_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_ALL_ENTITIES_COMMAND_H_
#define COMMANDS_CLEAR_ALL_ENTITIES_COMMAND_H_

#include "command.h"

class ClearAllEntitiesCommand : public Command
{
public:
	ClearAllEntitiesCommand() {}

    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<ClearAllEntitiesCommand>(); }
};


#endif /* COMMANDS_CLEAR_ALL_ENTITIES_COMMAND_H_ */
