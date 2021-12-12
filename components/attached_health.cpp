/*
 * attached_health.cpp
 *
 *  Created on: Nov 27, 2021
 *      Author: zamfi
 */

#include "attached_health.h"
#include "health.h"

double AttachedHealth::hp() const
{
	return m_health_accessor(m_attached_id).hp() + m_offset_hp;
}

double AttachedHealth::max_hp() const
{
	return m_health_accessor(m_attached_id).max_hp() + m_offset_max_hp;
}
