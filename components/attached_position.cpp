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
	try
	{
	    return globals.entity_system.entity(m_attached_id).position()->x() + m_offset_x;
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
	return 0;
}

double AttachedPosition::y() const
{
	try
	{
	    return globals.entity_system.entity(m_attached_id).position()->y() + m_offset_y;
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
	return 0;
}

double AttachedPosition::w() const
{
	try
	{
	    return globals.entity_system.entity(m_attached_id).position()->w() + m_offset_w;
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
	return 0;
}

double AttachedPosition::h() const
{
	try
	{
	    return globals.entity_system.entity(m_attached_id).position()->h() + m_offset_h;
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
	return 0;
}

