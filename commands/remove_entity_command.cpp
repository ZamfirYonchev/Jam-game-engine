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
	if(entity_system().previous_entity())
		entity_system().remove_entity(entity_system().previous_entity()->id());
	else
	{
		//error entity_system().previous_entity()
	}
}

