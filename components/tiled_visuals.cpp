/*
 * tiled_visuals.cpp
 *
 *  Created on: Dec 4, 2021
 *      Author: zamfi
 */

#include "tiled_visuals.h"
#include "position.h"

int TiledVisuals::repeat_x() const
{
	return std::ceil(m_position_accessor(m_self_id).w()/m_tile_w);
}

int TiledVisuals::repeat_y() const
{
	return std::ceil(m_position_accessor(m_self_id).h()/m_tile_h);
}

void TiledVisuals::set_repeat_x(const int val)
{
	m_tile_w = m_position_accessor(m_self_id).w()/val;
}

void TiledVisuals::set_repeat_y(const int val)
{
	m_tile_h = m_position_accessor(m_self_id).h()/val;
}
