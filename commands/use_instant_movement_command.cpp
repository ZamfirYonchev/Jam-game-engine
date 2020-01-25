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
	globals.entity_system.entity(globals.access_entity_id)->set_movement(new InstantMovement(m_move_accel));
}
