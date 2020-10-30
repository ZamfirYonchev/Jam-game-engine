/*
 * constant_control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_CONSTANT_CONTROL_H_
#define COMPONENTS_CONSTANT_CONTROL_H_

#include "control.h"
#include "../math_ext.h"

class ConstantControl : public Control
{
public:
	using Base = Control;
	ConstantControl(double move_decision, double jump_decision, double duck_decision, LookDir look_dir)
	: m_move_decision(clip(move_decision, -1.0, 1.0))
	, m_jump_decision(clip(jump_decision, 0.0, 1.0))
	, m_duck_decision(clip(duck_decision, 0.0, 1.0))
	, m_look_dir(look_dir)
	{}

    void print(std::ostream& to) const
    {
    	to << "UseConstantControl "
    	   << m_move_decision << " "
    	   << m_jump_decision << " "
    	   << m_duck_decision << " "
    	   << int(m_look_dir) << " ";
    }

    double decision_jump() const { return m_jump_decision; }
    double decision_duck() const { return m_duck_decision; }
    bool decision_attack() const { return false; }
    double decision_walk() const { return m_move_decision; }
    ProcedureID attack_proc_id() const { return ProcedureID{-1}; }
    LookDir look_dir() const { return m_look_dir; }

    void set_decision_jump(double val) { m_jump_decision = clip(val, 0.0, 1.0); }
    void set_decision_duck(double val) { m_duck_decision = clip(val, 0.0, 1.0); }
    void set_decision_attack(bool val) {}
    void set_decision_walk(double val) { m_move_decision = clip(val, -1.0, 1.0); }
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
    double m_move_decision, m_jump_decision, m_duck_decision;
    LookDir m_look_dir;
};

#endif /* COMPONENTS_CONSTANT_CONTROL_H_ */
