/*
 * input_control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_INPUT_CONTROL_H_
#define COMPONENTS_INPUT_CONTROL_H_

#include "control_enums.h"
#include "../math_ext.h"
#include "../systems/input_system.h"
#include "../types.h"
#include "../command_value.h"

class Movement;

class InputControl
{
public:
	InputControl
		(const ProcedureID shoot_proc_id
	   , const int shoot_cooldown
	   , const bool stability_control
	   , InputSystem& input_system
	   , const EntityID self_id
	   , const ComponentAccess<const Movement>& movement_accessor
	   )
    : m_self_id(self_id)
	, m_walk_dir(0)
    , m_vertical_dir(0)
    , m_shoot(false)
    , m_shoot_proc_id(shoot_proc_id)
    , m_shoot_cooldown(shoot_cooldown)
	, m_current_shoot_cooldown(shoot_cooldown)
	, m_look_dir(LookDir::RIGHT)
	, m_stability_control(stability_control)
	, m_input_system(input_system)
	, m_movement_accessor{movement_accessor}
    {}

    template<typename ExtractorF>
	InputControl
	( ExtractorF&& extract
	, InputSystem& input_system
	, const CommandValue& self_id
	, const ComponentAccess<const Movement>& movement_accessor
	)
	: InputControl
	  { extract().integer() //shoot_proc_id
	  , extract().integer() //shoot cooldown
	  , extract().boolean() //stability control
	  , input_system
	  , EntityID(self_id.integer())
	  , movement_accessor
	  }
    {}

    void print(std::ostream& to) const
    {
    	to << "UseInputControl "
    	   << m_shoot_proc_id << " "
    	   << m_shoot_cooldown << " "
		   << m_stability_control << " ";
    }

    double decision_vertical() const { return m_vertical_dir; }
    bool decision_attack() const { return m_shoot; }
    double decision_walk() const { return m_walk_dir; }
    ProcedureID attack_proc_id() const { return m_shoot_proc_id; }
    LookDir look_dir() const { return m_look_dir; }

    void set_decision_vertical(double val) { m_vertical_dir = clip(val, -1.0, 1.0); }
    void set_decision_attack(bool val) { m_shoot = val; }
    void set_decision_walk(double val) { m_walk_dir = clip(val, -1.0, 1.0); }
    void mod_decision_vertical(double val) { set_decision_vertical(m_vertical_dir+val); }
    void mod_decision_walk(double val) { set_decision_walk(m_walk_dir+val); }
    void set_attack_proc_id(ProcedureID val) { m_shoot_proc_id = val; }
    void set_look_dir(LookDir val) { m_look_dir = val; }

    void update_decisions(const Time time_diff);
    void clear_decisions()
    {
        m_vertical_dir = 0.0;
        m_shoot = false;
        m_walk_dir = 0.0;
    }

    EntityID m_self_id;

private:
    double m_walk_dir, m_vertical_dir;
    bool m_shoot;
    ProcedureID m_shoot_proc_id;
    int m_shoot_cooldown;
    int m_current_shoot_cooldown;
    LookDir m_look_dir;
    bool m_stability_control;
    std::reference_wrapper<InputSystem> m_input_system;
    ComponentAccess<const Movement> m_movement_accessor;
};


#endif /* COMPONENTS_INPUT_CONTROL_H_ */
