/*
 * modify_control_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_control_command.h"
#include "../globals.h"
#include "../math_ext.h"
#include <cmath>

void ModifyControlCommand::execute() const
{
	if(globals.entity_system.entity(globals.access_entity_id))
	{
		Control* control = globals.entity_system.entity(globals.access_entity_id)->control();

		if(m_decision_jump == 0 && std::signbit(m_decision_jump))
			control->set_decision_jump(false);
		else
			control->set_decision_jump(bool(m_decision_jump) ^ control->decision_jump());

		if(m_decision_duck == 0 && std::signbit(m_decision_duck))
			control->set_decision_duck(false);
		else
			control->set_decision_duck(bool(m_decision_duck) ^ control->decision_duck());

		if(m_decision_attack == 0 && std::signbit(m_decision_attack))
			control->set_decision_attack(false);
		else
			control->set_decision_attack(bool(m_decision_attack) ^ control->decision_attack());

		if(m_decision_walk == 0 && std::signbit(m_decision_walk))
			control->set_decision_walk(0);
		else
			control->set_decision_walk(clip(int8_t(m_decision_walk) + control->decision_walk(), -1, 1));

		if(m_look_dir == 0 && std::signbit(m_look_dir))
			control->set_look_dir(Control::RIGHT);
		else
			control->set_look_dir(Control::LookDir(bool(m_look_dir) ^ bool(control->look_dir())));
	}
	else
	{
		//error globals.access_entity_id
	}
}
