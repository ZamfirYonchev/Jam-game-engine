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
	Entity& entity = entity_system().add_new_entity();
    entity_system().add_accessed_entity(entity.id());
}
