/*
 * modify_movement_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_movement_command.h"
#include "../globals.h"
#include "../math_ext.h"

void ModifyMovementCommand::execute() const
{
	if(entity_system().entity(globals().access_entity_id))
	{
		Movement* movement = entity_system().entity(globals().access_entity_id)->movement();

		if(is_negative_zero(m_ax))
			movement->set_accel_x(m_ax);
		else
			movement->mod_accel_x(m_ax);

		if(is_negative_zero(m_ay))
			movement->set_accel_y(m_ay);
		else
			movement->mod_accel_y(m_ay);

		if(is_negative_zero(m_vx))
			movement->set_velocity_x(m_vx);
		else
			movement->mod_velocity_x(m_vx);

		if(is_negative_zero(m_vy))
			movement->set_velocity_y(m_vy);
		else
			movement->mod_velocity_y(m_vy);

		if(is_negative_zero(m_gravity_affected))
			movement->set_gravity_affected(bool(m_gravity_affected));
		else
			movement->set_gravity_affected(bool(m_gravity_affected) ^ movement->gravity_affected());
	}
	else
	{
		//error globals().access_entity_id
	}
}
