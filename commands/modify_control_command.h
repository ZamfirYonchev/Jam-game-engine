/*
 * modify_control_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_CONTROL_COMMAND_H_
#define COMMANDS_MODIFY_CONTROL_COMMAND_H_

#include "../math_ext.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ModifyControlCommand
{
public:
	ModifyControlCommand(double decision_jump, double decision_duck, double decision_attack, double decision_walk, double look_dir)
	: m_decision_jump(decision_jump)
	, m_decision_duck(decision_duck)
	, m_decision_attack(decision_attack)
	, m_decision_walk(decision_walk)
	, m_look_dir(look_dir)
	{}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	Control& control = entity_system.entity_component(entity_system.previous_entity_id(), (Control*)nullptr);

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
				control.set_look_dir(Control::LookDir::RIGHT);
			else
				control.set_look_dir(Control::LookDir(bool(m_look_dir) ^ bool(control.look_dir())));
		}
		else
		{
			//error entity_system.previous_entity_id()
		}
	}

private:
    double m_decision_jump;
    double m_decision_duck;
    double m_decision_attack;
    double m_decision_walk;
    double m_look_dir;
};


#endif /* COMMANDS_MODIFY_CONTROL_COMMAND_H_ */
