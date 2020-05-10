/*
 * attached_health.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "attached_health.h"
#include "../globals.h"

double AttachedHealth::hp() const
{
	if(globals.entity_system.entity(m_attached_id))
	{
		return globals.entity_system.entity(m_attached_id)->health()->hp() + m_offset_hp;
	}
	else
	{
		//error m_attached_id
		return 0;
	}
}

double AttachedHealth::max_hp() const
{
	if(globals.entity_system.entity(m_attached_id))
	{
		return globals.entity_system.entity(m_attached_id)->health()->max_hp() + m_offset_max_hp;
	}
	else
	{
		//error m_attached_id
		return 0;
	}
}
