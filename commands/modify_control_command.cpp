/*
 * modify_control_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_control_command.h"
#include "../globals.h"
#include "../math_ext.h"

void ModifyControlCommand::execute() const
{
	if(entity_system().previous_entity())
	{
		Control* control = entity_system().previous_entity()->control();

		if(is_negative_zero(m_decision_jump))
			control->set_decision_jump(0.0);
		else
			control->set_decision_jump(m_decision_jump + control->decision_jump());

		if(is_negative_zero(m_decision_duck))
			control->set_decision_duck(0.0);
		else
			control->set_decision_duck(m_decision_duck + control->decision_duck());

		if(is_negative_zero(m_decision_attack))
			control->set_decision_attack(false);
		else
			control->set_decision_attack(bool(m_decision_attack) ^ control->decision_attack());

		if(is_negative_zero(m_decision_walk))
			control->set_decision_walk(0);
		else
			control->set_decision_walk(m_decision_walk + control->decision_walk());

		if(is_negative_zero(m_look_dir))
			control->set_look_dir(Control::RIGHT);
		else
			control->set_look_dir(Control::LookDir(bool(m_look_dir) ^ bool(control->look_dir())));
	}
	else
	{
		//error globals().access_entity_id
	}
}
