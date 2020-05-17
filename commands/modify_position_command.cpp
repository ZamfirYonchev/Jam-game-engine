/*
 * modify_position_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_position_command.h"
#include "../globals.h"
#include <cmath>

void ModifyPositionCommand::execute() const
{
	if(entity_system().entity(globals().access_entity_id))
	{
		Position* position = entity_system().entity(globals().access_entity_id)->position();

		if(m_x == 0 && std::signbit(m_x))
			position->set_x(m_x);
		else
			position->mod_x(m_x);

		if(m_y == 0 && std::signbit(m_y))
			position->set_y(m_y);
		else
			position->mod_y(m_y);

		if(m_w == 0 && std::signbit(m_w))
			position->set_w(m_w);
		else
			position->mod_w(m_w);

		if(m_h == 0 && std::signbit(m_h))
			position->set_h(m_h);
		else
			position->mod_h(m_h);
	}
	else
	{
		//error globals().access_entity_id
	}
}
