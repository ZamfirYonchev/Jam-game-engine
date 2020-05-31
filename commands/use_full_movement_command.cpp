/*
 * use_full_movement_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_full_movement_command.h"
#include "../globals.h"
#include "../components/full_movement.h"

void UseFullMovementCommand::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_movement(new FullMovement(m_max_vx, m_max_vy, m_move_accel, m_jump_accel, m_gravity_affected));
	else
	{
		//error globals().access_entity_id
	}
}
