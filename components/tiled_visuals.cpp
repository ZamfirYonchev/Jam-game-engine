/*
 * tiled_visuals.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: zamfi
 */

#include "tiled_visuals.h"
#include "../globals.h"

uint16_t TiledVisuals::repeat_x() const
{
	return std::ceil(entity_system().entity(m_self_id)->position()->w()/m_tile_w);
}

uint16_t TiledVisuals::repeat_y() const
{
	return std::ceil(entity_system().entity(m_self_id)->position()->h()/m_tile_h);
}

void TiledVisuals::set_repeat_x(uint16_t val)
{
	m_tile_w = entity_system().entity(m_self_id)->position()->w()/val;
}

void TiledVisuals::set_repeat_y(uint16_t val)
{
	m_tile_h = entity_system().entity(m_self_id)->position()->h()/val;
}
