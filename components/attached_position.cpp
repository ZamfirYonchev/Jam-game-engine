/*
 * attached_position.cpp
 *
 *  Created on: Nov 27, 2021
 *      Author: zamfi
 */

#include "attached_position.h"
#include "position.h"
#include "../utilities.h"

double AttachedPosition::x() const
{
	return m_position_accessor(m_attached_id).x()
		+ absolute_or_scaled(m_offset_x, m_position_accessor(m_attached_id).w());
}

double AttachedPosition::y() const
{
	return m_position_accessor(m_attached_id).y()
		+ absolute_or_scaled(m_offset_y, m_position_accessor(m_attached_id).h());
}

double AttachedPosition::w() const
{
	return m_position_accessor(m_attached_id).w()
		 + absolute_or_scaled(m_offset_w, m_position_accessor(m_attached_id).w());
}

double AttachedPosition::h() const
{
	return m_position_accessor(m_attached_id).h()
		 + absolute_or_scaled(m_offset_h, m_position_accessor(m_attached_id).h());
}
