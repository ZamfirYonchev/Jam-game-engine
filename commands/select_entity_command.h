/*
 * select_entity_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_SELECT_ENTITY_COMMAND_H_
#define COMMANDS_SELECT_ENTITY_COMMAND_H_

#include "command.h"
#include "../types.h"

class SelectEntityCommand : public Command
{
public:
	SelectEntityCommand(EntityID id)
	: m_id(id)
	{}

    void execute() const;
    Command* clone() { return new SelectEntityCommand(m_id); }

private:
    EntityID m_id;
};

#endif /* COMMANDS_SELECT_ENTITY_COMMAND_H_ */
