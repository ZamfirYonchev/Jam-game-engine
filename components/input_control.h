/*
 * input_control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_INPUT_CONTROL_H_
#define COMPONENTS_INPUT_CONTROL_H_

#include "control.h"
#include "../input_handler.h"

class InputControl : public Control
{
public:
	using Base = Control;
    InputControl(InputHandler* input, ProcedureID shoot_proc_id, double shoot_cooldown, EntityID self_id)
    : m_input(input)
    , m_walk_dir(0)
    , m_jump(false)
	, m_duck(false)
    , m_shoot(false)
    , m_shoot_proc_id(shoot_proc_id)
    , m_shoot_cooldown(shoot_cooldown)
	, m_current_shoot_cooldown(0)
	, m_look_dir(RIGHT)
	, m_self_id(self_id)
    {}

    InputControl(InputHandler* input, EntityID self_id) : InputControl(input, -1, 0, self_id) {}
    InputControl() : InputControl(nullptr, 0) {}

    void print(std::ostream& to) const
    {
    	to << "UseInputControl "
    	   << m_shoot_proc_id << " "
    	   << m_shoot_cooldown << " ";
    }

    bool decision_jump() const { return m_jump; }
    bool decision_duck() const { return m_duck; }
    bool decision_attack() const { return m_shoot; }
    int8_t decision_walk() const { return m_walk_dir; }
    ProcedureID attack_proc_id() const { return m_shoot_proc_id; }
    LookDir look_dir() const { return m_look_dir; }

    void set_decision_jump(bool val) { m_jump = val; }
    void set_decision_duck(bool val) { m_duck = val; }
    void set_decision_attack(bool val) { m_shoot = val; }
    void set_decision_walk(int8_t val) { m_walk_dir = val; }
    void set_attack_proc_id(ProcedureID val) { m_shoot_proc_id = val; }
    void set_look_dir(LookDir val) { m_look_dir = val; }

    void update_decisions(Time time_diff);
    void clear_decisions()
    {
        m_jump = false;
        m_duck = false;
        m_shoot = false;
        m_walk_dir = 0;
    }

private:
    InputHandler* m_input;
    int8_t m_walk_dir;
    bool m_jump;
    bool m_duck;
    bool m_shoot;
    ProcedureID m_shoot_proc_id;
    int m_shoot_cooldown;
    int m_current_shoot_cooldown;
    LookDir m_look_dir;
    EntityID m_self_id;
};


#endif /* COMPONENTS_INPUT_CONTROL_H_ */
