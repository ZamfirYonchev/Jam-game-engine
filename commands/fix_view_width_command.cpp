/*
 * fix_view_width_command.cpp
 *
 *  Created on: May 23, 2020
 *      Author: zamfi
 */

#include "fix_view_width_command.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"
#include "../globals.h"

void FixViewWidthCommand::execute() const
{
	auto& position = system<EntitySystem>().entity(EntityID{0})->component<Position>();
	if(system<EntitySystem>().entity(EntityID{0}))
		position.set_w(int(position.h()*globals().resolution_x/globals().resolution_y));
	else
	{
		//error system<EntitySystem>().entity(0)
	}
}
