/*
 * character_health_visuals.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "health_visuals.h"
#include "health.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

uint8_t HealthVisuals::animation_sprite(uint16_t rx, uint16_t ry) const
{
	const auto& health = system<EntitySystem>().entity_component<Health>(m_self_id);
	return (m_repeat_x != 0) && (health.max_hp() != 0) && (1.0*rx/m_repeat_x) < (1.0*health.hp()/health.max_hp());
}
