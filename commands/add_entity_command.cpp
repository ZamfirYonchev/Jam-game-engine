/*
 * add_entity_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_entity_command.h"
#include "../globals.h"

void AddEntityCommand::execute() const
{
	entity_system().add_new_entity();
    globals().access_entity_id = entity_system().last_id();
}
