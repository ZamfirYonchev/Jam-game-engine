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
    Command* clone() { return new AddEntityCommand(); }
};


#endif /* COMMANDS_ADD_ENTITY_COMMAND_H_ */
