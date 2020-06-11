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
	if(entity_system().previous_entity())
	{
		Movement* movement = entity_system().previous_entity()->movement();

		if(is_negative_zero(m_mass))
			movement->set_mass(m_mass);
		else
			movement->set_mass(movement->mass() + m_mass);

		if(is_negative_zero(m_friction))
			movement->set_friction(m_friction);
		else
			movement->set_friction(movement->friction() + m_friction);

		if(is_negative_zero(m_fx))
			movement->set_force_x(m_fx);
		else
			movement->mod_force_x(m_fx);

		if(is_negative_zero(m_fy))
			movement->set_force_y(m_fy);
		else
			movement->mod_force_y(m_fy);

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
