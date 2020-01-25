/*
 * modify_movement_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_movement_command.h"
#include "../globals.h"
#include <cmath>

void ModifyMovementCommand::execute() const
{
	if(m_ax == 0 && std::signbit(m_ax))
		globals.entity_system.entity(globals.access_entity_id)->movement()->set_accel_x(m_ax);
	else
		globals.entity_system.entity(globals.access_entity_id)->movement()->mod_accel_x(m_ax);

	if(m_ay == 0 && std::signbit(m_ay))
		globals.entity_system.entity(globals.access_entity_id)->movement()->set_accel_y(m_ay);
	else
		globals.entity_system.entity(globals.access_entity_id)->movement()->mod_accel_y(m_ay);

	if(m_vx == 0 && std::signbit(m_vx))
		globals.entity_system.entity(globals.access_entity_id)->movement()->set_velocity_x(m_vx);
	else
		globals.entity_system.entity(globals.access_entity_id)->movement()->mod_velocity_x(m_vx);

	if(m_vy == 0 && std::signbit(m_vy))
		globals.entity_system.entity(globals.access_entity_id)->movement()->set_velocity_y(m_vy);
	else
		globals.entity_system.entity(globals.access_entity_id)->movement()->mod_velocity_y(m_vy);

	if(m_gravity_affected == 0 && std::signbit(m_gravity_affected))
		globals.entity_system.entity(globals.access_entity_id)->movement()->set_gravity_affected(bool(m_gravity_affected));
	else
		globals.entity_system.entity(globals.access_entity_id)->movement()->set_gravity_affected(bool(m_gravity_affected) ^ globals.entity_system.entity(globals.access_entity_id)->movement()->gravity_affected());

}
