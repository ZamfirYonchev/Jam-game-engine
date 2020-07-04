/*
 * constant_control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_CONSTANT_CONTROL_H_
#define COMPONENTS_CONSTANT_CONTROL_H_

#include "control.h"

class ConstantControl : public Control
{
public:
	using Base = Control;
	ConstantControl(int8_t move_decision, bool jump_decision, bool duck_decision, LookDir look_dir)
	: m_move_decision(move_decision)
	, m_jump_decision(jump_decision)
	, m_duck_decision(duck_decision)
	, m_look_dir(look_dir)
	{}

    void print(std::ostream& to) const
    {
    	to << "UseConstantControl "
    	   << m_move_decision << " "
    	   << m_jump_decision << " "
    	   << m_duck_decision << " "
    	   << m_look_dir << " ";
    }

    bool decision_jump() const { return m_jump_decision; }
    bool decision_duck() const { return m_duck_decision; }
    bool decision_attack() const { return false; }
    int8_t decision_walk() const { return m_move_decision; }
    ProcedureID attack_proc_id() const { return ProcedureID{-1}; }
    LookDir look_dir() const { return m_look_dir; }

    void set_decision_jump(bool val) { m_jump_decision = val; }
    void set_decision_duck(bool val) { m_duck_decision = val; }
    void set_decision_attack(bool val) {}
    void set_decision_walk(int8_t val) { m_move_decision = val; }
    void set_attack_proc_id(ProcedureID val) {}
    void set_look_dir(LookDir val) { m_look_dir = val; }

    void update_decisions(const Time time) {}
    void clear_decisions()
    {
    	m_move_decision = 0;
    	m_jump_decision = false;
    	m_duck_decision = false;
    }

private:
    int8_t m_move_decision;
    bool m_jump_decision, m_duck_decision;
    LookDir m_look_dir;
};

#endif /* COMPONENTS_CONSTANT_CONTROL_H_ */
