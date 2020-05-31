/*
 * use_attached_position_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_attached_position_command.h"
#include "../globals.h"
#include "../utilities.h"
#include "../components/attached_position.h"

void UseAttachedPositionCommand::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_position(new AttachedPosition(resolved_entity(m_id), m_offset_x, m_offset_y, m_offset_w, m_offset_h));
	else
	{
		//error globals().access_entity_id
	}
}
