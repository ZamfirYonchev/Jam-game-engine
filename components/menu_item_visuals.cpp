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
	const auto& control = system<EntitySystem>().entity_component<Control>(m_self_id);
	return control.decision_attack() ? 2 : control.decision_jump() ? 1 : 0;
}
