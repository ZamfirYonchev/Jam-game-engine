/*
 * modify_control_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_control_command.h"
#include "../math_ext.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

void ModifyControlCommand::execute() const
{
	auto& control = system<EntitySystem>().entity_component<Control>(system<EntitySystem>().previous_entity_id());
	if(control)
	{
		if(is_negative_zero(m_decision_jump))
			control.set_decision_jump(0.0);
		else
			control.set_decision_jump(m_decision_jump + control.decision_jump());

		if(is_negative_zero(m_decision_duck))
			control.set_decision_duck(0.0);
		else
			control.set_decision_duck(m_decision_duck + control.decision_duck());

		if(is_negative_zero(m_decision_attack))
			control.set_decision_attack(false);
		else
			control.set_decision_attack(bool(m_decision_attack) ^ control.decision_attack());

		if(is_negative_zero(m_decision_walk))
			control.set_decision_walk(0);
		else
			control.set_decision_walk(m_decision_walk + control.decision_walk());

		if(is_negative_zero(m_look_dir))
			control.set_look_dir(Control::RIGHT);
		else
			control.set_look_dir(Control::LookDir(bool(m_look_dir) ^ bool(control.look_dir())));
	}
	else
	{
		//error globals().access_entity_id
	}
}
