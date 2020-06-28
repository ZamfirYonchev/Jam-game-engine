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
	InputSelectControl(InputHandler* input, int select, int max, ProcedureID proc_id)
    : m_input(input)
	, m_select(select)
	, m_max(max)
	, m_curr_selection(0)
    , m_proc_id(proc_id)
    {}

    InputSelectControl() : InputSelectControl(nullptr, 0, 0, -1) {}

    void print(std::ostream& to) const
    {
    	to << "UseInputSelectControl "
    	   << m_select << " "
    	   << m_max << " "
    	   << m_proc_id << " ";
    }

    bool decision_jump() const { return m_select == m_curr_selection; }
    bool decision_duck() const { return false; }
    bool decision_attack() const
    {
    	return m_select == m_curr_selection && m_input->select();
    }

    int8_t decision_walk() const { return false; }
    ProcedureID attack_proc_id() const { return m_proc_id; }
    LookDir look_dir() const { return RIGHT; }

    void set_decision_jump(bool val) {}
    void set_decision_duck(bool val) {}
    void set_decision_attack(bool val) {}
    void set_decision_walk(int8_t val) {}
    void set_attack_proc_id(ProcedureID val) { m_proc_id = val; }
    void set_look_dir(LookDir val) {}

    void update_decisions(int32_t time_diff)
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
