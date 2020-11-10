/*
 * input_select_control.h
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_INPUT_SELECT_CONTROL_H_
#define COMPONENTS_INPUT_SELECT_CONTROL_H_

#include "control.h"

class InputSystem;

class InputSelectControl : public Control
{
public:
	using Base = Control;
	InputSelectControl(const int select, const int max, const ProcedureID proc_id, InputSystem& input_system)
    : m_select(select)
	, m_max(max)
	, m_curr_selection(0)
    , m_proc_id(proc_id)
	, m_input_system(input_system)
    {}

    void print(std::ostream& to) const
    {
    	to << "UseInputSelectControl "
    	   << m_select << " "
    	   << m_max << " "
    	   << m_proc_id << " ";
    }

    double decision_vertical() const { return m_select == m_curr_selection; }
    bool decision_attack() const;

    double decision_walk() const { return 0.0; }
    ProcedureID attack_proc_id() const { return m_proc_id; }
    LookDir look_dir() const { return LookDir::RIGHT; }

    void set_decision_vertical(double val) {}
    void set_decision_attack(bool val) {}
    void set_decision_walk(double val) {}
    void mod_decision_vertical(double val) {}
    void mod_decision_walk(double val) {}
    void set_attack_proc_id(ProcedureID val) { m_proc_id = val; }
    void set_look_dir(LookDir val) {}

    void update_decisions(const Time time_diff);
    void clear_decisions() {}

private:
    int m_select, m_max, m_curr_selection;
    ProcedureID m_proc_id;
    InputSystem& m_input_system;
};

#endif /* COMPONENTS_INPUT_SELECT_CONTROL_H_ */
