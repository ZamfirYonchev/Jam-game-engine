/*
 * input_select_control.h
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_INPUT_SELECT_CONTROL_H_
#define COMPONENTS_INPUT_SELECT_CONTROL_H_

#include "control.h"
#include "../input_handler.h"

class InputSelectControl : public Control
{
public:
	using Base = Control;
	InputSelectControl(InputHandler* input, const int select, const int max, const ProcedureID proc_id)
    : m_input(input)
	, m_select(select)
	, m_max(max)
	, m_curr_selection(0)
    , m_proc_id(proc_id)
    {}

    InputSelectControl() : InputSelectControl(nullptr, 0, 0, ProcedureID{-1}) {}

    void print(std::ostream& to) const
    {
    	to << "UseInputSelectControl "
    	   << m_select << " "
    	   << m_max << " "
    	   << m_proc_id << " ";
    }

    double decision_jump() const { return m_select == m_curr_selection; }
    double decision_duck() const { return 0.0; }
    bool decision_attack() const
    {
    	return m_select == m_curr_selection && m_input->select();
    }

    double decision_walk() const { return 0.0; }
    ProcedureID attack_proc_id() const { return m_proc_id; }
    LookDir look_dir() const { return RIGHT; }

    void set_decision_jump(double val) {}
    void set_decision_duck(double val) {}
    void set_decision_attack(bool val) {}
    void set_decision_walk(double val) {}
    void set_attack_proc_id(ProcedureID val) { m_proc_id = val; }
    void set_look_dir(LookDir val) {}

    void update_decisions(const Time time_diff)
    {
    	m_curr_selection += m_input->down() - m_input->up() + m_max;
    	m_curr_selection %= m_max;
    }

    void clear_decisions() {}

private:
    InputHandler* m_input;
    int m_select, m_max, m_curr_selection;
    ProcedureID m_proc_id;
};

#endif /* COMPONENTS_INPUT_SELECT_CONTROL_H_ */
