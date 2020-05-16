/*
 * use_absolute_position_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_absolute_position_command.h"
#include "../globals.h"

void UseAbsolutePositionCommand::execute() const
{
	entity_system().entity(globals().access_entity_id)->set_position(new AbsolutePosition(m_position));
}
