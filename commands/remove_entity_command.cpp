/*
 * remove_entity_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "remove_entity_command.h"
#include "../globals.h"

void RemoveEntityCommand::execute() const
{
	entity_system().remove_entity(globals().access_entity_id);
}

