/*
 * menu_item_visuals.cpp
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#include "menu_item_visuals.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

uint8_t MenuItemVisuals::animation_sprite(uint16_t rx, uint16_t ry) const
{
	if(system<EntitySystem>().entity(m_self_id))
	{
		const auto& control = system<EntitySystem>().entity(m_self_id)->component<Control>();
		return control.decision_attack() ? 2 : control.decision_jump() ? 1 : 0;
	}
	else
	{
		//error m_self_id
		return 0;
	}
}
