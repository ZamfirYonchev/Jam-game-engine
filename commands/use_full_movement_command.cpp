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
		entity_system().previous_entity()->set_movement(new FullMovement(m_mass, m_friction, m_move_force, m_jump_force, m_gravity_affected));
	else
	{
		//error globals().access_entity_id
	}
}
