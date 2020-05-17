/*
 * character_health_visuals.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "character_health_visuals.h"
#include "health.h"
#include "../globals.h"

uint8_t CharacterHealthVisuals::animation_sprite(uint16_t rx, uint16_t ry) const
{
	if(entity_system().entity(m_self_id))
	{
		Health* health = entity_system().entity(m_self_id)->health();
		return (m_repeat_x != 0) && (health->max_hp() != 0) && (1.0*rx/m_repeat_x) < (1.0*health->hp()/health->max_hp());
	}
	else
	{
		//error m_self_id
		return 0;
	}
}
