/*
 * input_control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_INPUT_CONTROL_H_
#define COMPONENTS_INPUT_CONTROL_H_

#include "control.h"
#include "../math_ext.h"

class InputControl : public Control
{
public:
	using Base = Control;
    InputControl(ProcedureID shoot_proc_id, double shoot_cooldown, EntityID self_id, bool stability_control)
    : m_walk_dir(0)
    , m_jump(false)
	, m_duck(false)
    , m_shoot(false)
    , m_shoot_proc_id(shoot_proc_id)
    , m_shoot_cooldown(shoot_cooldown)
	, m_current_shoot_cooldown(shoot_cooldown)
	, m_look_dir(RIGHT)
	, m_self_id(self_id)
	, m_stability_control(stability_control)
    {}

    InputControl(EntityID self_id) : InputControl(ProcedureID{-1}, 0, self_id, false) {}
    InputControl() : InputControl(EntityID{0}) {}

    void print(std::ostream& to) const
    {
    	to << "UseInputControl "
    	   << m_shoot_proc_id << " "
    	   << m_shoot_cooldown << " "
		   << m_stability_control << " ";
    }

    double decision_jump() const { return m_jump; }
    double decision_duck() const { return m_duck; }
    bool decision_attack() const { return m_shoot; }
    double decision_walk() const { return m_walk_dir; }
    ProcedureID attack_proc_id() const { return m_shoot_proc_id; }
    LookDir look_dir() const { return m_look_dir; }

    void set_decision_jump(double val) { m_jump = clip(val, 0.0, 1.0); }
    void set_decision_duck(double val) { m_duck = clip(val, 0.0, 1.0); }
    void set_decision_attack(bool val) { m_shoot = val; }
    void set_decision_walk(double val) { m_walk_dir = clip(val, -1.0, 1.0); }
    void set_attack_proc_id(ProcedureID val) { m_shoot_proc_id = val; }
    void set_look_dir(LookDir val) { m_look_dir = val; }

    void update_decisions(const Time time_diff);
    void clear_decisions()
    {
        m_jump = 0.0;
        m_duck = 0.0;
        m_shoot = false;
        m_walk_dir = 0.0;
    }

private:
    double m_walk_dir, m_jump, m_duck;
    bool m_shoot;
    ProcedureID m_shoot_proc_id;
    int m_shoot_cooldown;
    int m_current_shoot_cooldown;
    LookDir m_look_dir;
    EntityID m_self_id;
    bool m_stability_control;
};


#endif /* COMPONENTS_INPUT_CONTROL_H_ */
