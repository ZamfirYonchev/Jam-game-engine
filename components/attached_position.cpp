/*
 * attached_position.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#include "attached_position.h"
#include "../utilities.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

double AttachedPosition::x() const
{
	return system<EntitySystem>().entity_component<Position>(m_attached_id).x()
		+ absolute_or_scaled(m_offset_x, system<EntitySystem>().entity_component<Position>(m_attached_id).w());
}

double AttachedPosition::y() const
{
	return system<EntitySystem>().entity_component<Position>(m_attached_id).y()
		+ absolute_or_scaled(m_offset_y, system<EntitySystem>().entity_component<Position>(m_attached_id).h());
}

double AttachedPosition::w() const
{
	return system<EntitySystem>().entity_component<Position>(m_attached_id).w()
		 + absolute_or_scaled(m_offset_w, system<EntitySystem>().entity_component<Position>(m_attached_id).w());
}

double AttachedPosition::h() const
{
	return system<EntitySystem>().entity_component<Position>(m_attached_id).h()
		 + absolute_or_scaled(m_offset_h, system<EntitySystem>().entity_component<Position>(m_attached_id).h());
}

