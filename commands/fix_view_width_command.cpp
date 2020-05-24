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
	if(entity_system().entity(0))
		entity_system().entity(0)->position()->set_w(int(entity_system().entity(0)->position()->h()*globals().resolution_x/globals().resolution_y));
	else
	{
		//error entity_system().entity(0)
	}
}