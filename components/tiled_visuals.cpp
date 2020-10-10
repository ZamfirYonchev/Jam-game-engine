/*
 * tiled_visuals.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: zamfi
 */

#include "tiled_visuals.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"
#include "../math_ext.h"

uint16_t TiledVisuals::repeat_x() const
{
	return std::ceil(system<EntitySystem>().entity_component<Position>(m_self_id).w()/m_tile_w);
}

uint16_t TiledVisuals::repeat_y() const
{
	return std::ceil(system<EntitySystem>().entity_component<Position>(m_self_id).h()/m_tile_h);
}

void TiledVisuals::set_repeat_x(uint16_t val)
{
	m_tile_w = system<EntitySystem>().entity_component<Position>(m_self_id).w()/val;
}

void TiledVisuals::set_repeat_y(uint16_t val)
{
	m_tile_h = system<EntitySystem>().entity_component<Position>(m_self_id).h()/val;
}
