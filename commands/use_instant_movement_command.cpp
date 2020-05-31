/*
 * use_instant_movement_command.cpp
 *
 *  Created on: Dec 8, 2019
 *      Author: zamfi
 */

#include "use_instant_movement_command.h"
#include "../globals.h"
#include "../components/instant_movement.h"

void UseInstantMovementCommand::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_movement(new InstantMovement(m_move_accel));
	else
	{
		//error globals().access_entity_id
	}
}
