/*
 * add_entity_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_ENTITY_COMMAND_H_
#define COMMANDS_ADD_ENTITY_COMMAND_H_

#include "command.h"

class AddEntityCommand : public Command
{
public:
    AddEntityCommand() {}
    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<AddEntityCommand>(); }
};


#endif /* COMMANDS_ADD_ENTITY_COMMAND_H_ */
