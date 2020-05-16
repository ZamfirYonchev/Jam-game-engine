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
	if(m_x == 0 && std::signbit(m_x))
		entity_system().entity(globals().access_entity_id)->position()->set_x(m_x);
	else
		entity_system().entity(globals().access_entity_id)->position()->mod_x(m_x);

	if(m_y == 0 && std::signbit(m_y))
		entity_system().entity(globals().access_entity_id)->position()->set_y(m_y);
	else
		entity_system().entity(globals().access_entity_id)->position()->mod_y(m_y);

	if(m_w == 0 && std::signbit(m_w))
		entity_system().entity(globals().access_entity_id)->position()->set_w(m_w);
	else
		entity_system().entity(globals().access_entity_id)->position()->mod_w(m_w);

	if(m_h == 0 && std::signbit(m_h))
		entity_system().entity(globals().access_entity_id)->position()->set_h(m_h);
	else
		entity_system().entity(globals().access_entity_id)->position()->mod_h(m_h);
}
