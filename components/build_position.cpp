/*
 * build_position.cpp
 *
 *  Created on: Nov 27, 2021
 *      Author: zamfi
 */

#include "build_position.h"
#include "position.h"
#include "../math_ext.h"

double BuildPosition::x() const
{
	return min(m_origin_x, m_position_accessor(m_attached_id).x());
}

double BuildPosition::y() const
{
	return min(m_origin_y, m_position_accessor(m_attached_id).y());
}

double BuildPosition::w() const
{
	return abs(m_origin_x - m_position_accessor(m_attached_id).x());
}

double BuildPosition::h() const
{
	return abs(m_origin_y - m_position_accessor(m_attached_id).y());
}

