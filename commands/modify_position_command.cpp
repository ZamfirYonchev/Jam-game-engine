/*
 * modify_position_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_position_command.h"
#include "../globals.h"
#include "../math_ext.h"

void ModifyPositionCommand::execute() const
{
	if(entity_system().entity(globals().access_entity_id))
	{
		Position* position = entity_system().entity(globals().access_entity_id)->position();

		if(is_negative_zero(m_x))
			position->set_x(m_x);
		else
			position->mod_x(m_x);

		if(is_negative_zero(m_y))
			position->set_y(m_y);
		else
			position->mod_y(m_y);

		if(is_negative_zero(m_w))
			position->set_w(m_w);
		else
			position->mod_w(m_w);

		if(is_negative_zero(m_h))
			position->set_h(m_h);
		else
			position->mod_h(m_h);
	}
	else
	{
		//error globals().access_entity_id
	}
}
