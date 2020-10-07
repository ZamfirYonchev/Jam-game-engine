/*
 * add_entity_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_entity_command.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

void AddEntityCommand::execute() const
{
	Entity& entity = system<EntitySystem>().add_new_entity();
    system<EntitySystem>().add_accessed_entity(entity.id());
}
