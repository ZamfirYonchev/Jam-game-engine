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
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_position(new AbsolutePosition(m_position));
	else
	{
		//error entity_system().previous_entity()
	}
}
