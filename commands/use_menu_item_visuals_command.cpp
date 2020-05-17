/*
 * use_menu_item_visuals_command.cpp
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#include "use_menu_item_visuals_command.h"
#include "../globals.h"
#include "../components/menu_item_visuals.h"

void UseMenuItemVisualsCommand::execute() const
{
	if(entity_system().entity(globals().access_entity_id))
		entity_system().entity(globals().access_entity_id)->set_visuals(new MenuItemVisuals(m_spr_id, globals().access_entity_id));
	else
	{
		//error globals().access_entity_id
	}
}
