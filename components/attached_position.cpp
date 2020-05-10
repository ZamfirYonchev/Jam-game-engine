/*
 * attached_position.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#include "attached_position.h"
#include "../globals.h"

double AttachedPosition::x() const
{
	if(globals.entity_system.entity(m_attached_id))
	{
	    return globals.entity_system.entity(m_attached_id)->position()->x() + m_offset_x;
	}
	else
	{
		//error m_attached_id
		return 0;
	}
}

double AttachedPosition::y() const
{
	if(globals.entity_system.entity(m_attached_id))
	{
		return globals.entity_system.entity(m_attached_id)->position()->y() + m_offset_y;
	}
	else
	{
		//error m_attached_id
		return 0;
	}
}

double AttachedPosition::w() const
{
	if(globals.entity_system.entity(m_attached_id))
	{
		return globals.entity_system.entity(m_attached_id)->position()->w() + m_offset_w;
	}
	else
	{
		//error m_attached_id
		return 0;
	}
}

double AttachedPosition::h() const
{
	if(globals.entity_system.entity(m_attached_id))
	{
		return globals.entity_system.entity(m_attached_id)->position()->h() + m_offset_h;
	}
	else
	{
		//error m_attached_id
		return 0;
	}
}

