/*
 * attached_health.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "attached_health.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

double AttachedHealth::hp() const
{
	return system<EntitySystem>().entity_component<Health>(m_attached_id).hp() + m_offset_hp;
}

double AttachedHealth::max_hp() const
{
	return system<EntitySystem>().entity_component<Health>(m_attached_id).max_hp() + m_offset_max_hp;
}
