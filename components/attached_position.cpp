/*
 * attached_position.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#include "attached_position.h"
#include "../utilities.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

double AttachedPosition::x() const
{
	if(system<EntitySystem>().entity(m_attached_id))
	{
	    return system<EntitySystem>().entity(m_attached_id)->component<Position>().x()
	    	 + absolute_or_scaled(m_offset_x, system<EntitySystem>().entity(m_attached_id)->component<Position>().w());
	}
	else
	{
		//error m_attached_id
		return 0;
	}
}

double AttachedPosition::y() const
{
	if(system<EntitySystem>().entity(m_attached_id))
	{
		return system<EntitySystem>().entity(m_attached_id)->component<Position>().y()
		+ absolute_or_scaled(m_offset_y, system<EntitySystem>().entity(m_attached_id)->component<Position>().h());
	}
	else
	{
		//error m_attached_id
		return 0;
	}
}

double AttachedPosition::w() const
{
	if(system<EntitySystem>().entity(m_attached_id))
	{
		return system<EntitySystem>().entity(m_attached_id)->component<Position>().w()
			 + absolute_or_scaled(m_offset_w, system<EntitySystem>().entity(m_attached_id)->component<Position>().w());
	}
	else
	{
		//error m_attached_id
		return 0;
	}
}

double AttachedPosition::h() const
{
	if(system<EntitySystem>().entity(m_attached_id))
	{
		return system<EntitySystem>().entity(m_attached_id)->component<Position>().h()
			 + absolute_or_scaled(m_offset_h, system<EntitySystem>().entity(m_attached_id)->component<Position>().h());
	}
	else
	{
		//error m_attached_id
		return 0;
	}
}

