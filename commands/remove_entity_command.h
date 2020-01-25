/*
 * remove_entity_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_REMOVE_ENTITY_COMMAND_H_
#define COMMANDS_REMOVE_ENTITY_COMMAND_H_

#include "command.h"

class RemoveEntityCommand : public Command
{
public:
    RemoveEntityCommand() {}

    void execute() const;
    Command* clone() { return new RemoveEntityCommand(); }
};


#endif /* COMMANDS_REMOVE_ENTITY_COMMAND_H_ */
