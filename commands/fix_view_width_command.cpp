/*
 * fix_view_width_command.cpp
 *
 *  Created on: May 23, 2020
 *      Author: zamfi
 */

#include "fix_view_width_command.h"
#include "../globals.h"

void FixViewWidthCommand::execute() const
{
	auto& position = entity_system().entity(EntityID{0})->component<Position>();
	if(entity_system().entity(EntityID{0}))
		position.set_w(int(position.h()*globals().resolution_x/globals().resolution_y));
	else
	{
		//error entity_system().entity(0)
	}
}
