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
	try
	{
		globals.entity_system.entity(globals.access_entity_id).set_movement(new FullMovement(m_max_vx, m_max_vy, m_move_accel, m_jump_accel, m_gravity_affected));
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}
