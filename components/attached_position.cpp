/*
 * attached_position.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#include "attached_position.h"
#include "../globals.h"
#include "../utilities.h"

double AttachedPosition::x() const
{
	if(entity_system().entity(m_attached_id))
	{
	    return entity_system().entity(m_attached_id)->position()->x()
	    	 + absolute_or_scaled(m_offset_x, entity_system().entity(m_attached_id)->position()->w());
	}
	else
	{
		//error m_attached_id
		return 0;
	}
}

double AttachedPosition::y() const
{
	if(entity_system().entity(m_attached_id))
	{
		return entity_system().entity(m_attached_id)->position()->y()
		+ absolute_or_scaled(m_offset_y, entity_system().entity(m_attached_id)->position()->h());
	}
	else
	{
		//error m_attached_id
		return 0;
	}
}

double AttachedPosition::w() const
{
	if(entity_system().entity(m_attached_id))
	{
		return entity_system().entity(m_attached_id)->position()->w()
			 + absolute_or_scaled(m_offset_w, entity_system().entity(m_attached_id)->position()->w());
	}
	else
	{
		//error m_attached_id
		return 0;
	}
}

double AttachedPosition::h() const
{
	if(entity_system().entity(m_attached_id))
	{
		return entity_system().entity(m_attached_id)->position()->h()
			 + absolute_or_scaled(m_offset_h, entity_system().entity(m_attached_id)->position()->h());
	}
	else
	{
		//error m_attached_id
		return 0;
	}
}

