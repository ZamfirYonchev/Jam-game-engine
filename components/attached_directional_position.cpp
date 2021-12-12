/*
 * attached_directional_position.cpp
 *
 *  Created on: Nov 27, 2021
 *      Author: zamfi
 */

#include "attached_directional_position.h"
#include "position.h"
#include "control.h"

double AttachedDirectionalPosition::x() const
{
	const Position& attached_position = m_position_accessor(m_attached_id);
	return attached_position.x()
		 + attached_position.w()/2
		 + m_offset_x * (1 - 2*(m_control_accessor(m_attached_id).look_dir() == LookDir::LEFT))
		 - m_w/2;
}

double AttachedDirectionalPosition::y() const
{
	const Position& attached_position = m_position_accessor(m_attached_id);
	return attached_position.y()
		 + attached_position.h()/2
		 + m_offset_y
		 - m_h/2;
}
