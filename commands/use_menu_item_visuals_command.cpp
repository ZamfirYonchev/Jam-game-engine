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
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_visuals(new MenuItemVisuals(m_spr_id, entity_system().previous_entity()->id()));
	else
	{
		//error globals().access_entity_id
	}
}
