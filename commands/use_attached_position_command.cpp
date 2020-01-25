/*
 * use_attached_position_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_attached_position_command.h"
#include "../globals.h"
#include "../components/attached_position.h"

void UseAttachedPositionCommand::execute() const
{
	globals.entity_system.entity(globals.access_entity_id)->set_position(new AttachedPosition(m_id, m_offset_x, m_offset_y, m_offset_w, m_offset_h));
}
