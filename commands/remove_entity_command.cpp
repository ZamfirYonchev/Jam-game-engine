/*
 * remove_entity_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "remove_entity_command.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

void RemoveEntityCommand::execute() const
{
	if(system<EntitySystem>().previous_entity())
		system<EntitySystem>().remove_entity(system<EntitySystem>().previous_entity()->id());
	else
	{
		//error system<EntitySystem>().previous_entity()
	}
}

