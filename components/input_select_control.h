/*
 * input_select_control.h
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_INPUT_SELECT_CONTROL_H_
#define COMPONENTS_INPUT_SELECT_CONTROL_H_

#include "../types.h"
#include "../systems/input_system.h"

class InputSelectControl
{
public:
	InputSelectControl
		(const int select
	   , const int max
	   , const ProcedureID proc_id
	   , const InputSystem& input_system)
    : m_select(select)
	, m_max(max)
	, m_curr_selection(0)
    , m_proc_id(proc_id)
	, m_input_system(input_system)
    {}

    template<typename ExtractorF>
	InputSelectControl
	( ExtractorF&& extract
	, const InputSystem& input_system
	)
	: InputSelectControl
	  { extract()
	  , extract()
	  , extract()
	  , input_system
	  }
    {}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseInputSelectControl");
    	insert(m_select);
    	insert(m_max);
    	insert(m_proc_id);
    }

    double decision_vertical() const { return m_select == m_curr_selection; }
    bool decision_attack() const
    {
    	return m_select == m_curr_selection && m_input_system.get().select();
    }

    double decision_walk() const { return 0.0; }
    ProcedureID attack_proc_id() const { return m_proc_id; }

    void set_decision_vertical(double) {}
    void set_decision_attack(bool) {}
    void set_decision_walk(double) {}
    void mod_decision_vertical(double) {}
    void mod_decision_walk(double) {}
    void set_attack_proc_id(ProcedureID val) { m_proc_id = val; }

    void update_decisions(const Time time_diff)
    {
    	m_curr_selection += m_input_system.get().down() - m_input_system.get().up() + m_max;
    	m_curr_selection %= m_max;
    }

    void clear_decisions() {}

private:
    int m_select, m_max, m_curr_selection;
    ProcedureID m_proc_id;
    std::reference_wrapper<const InputSystem> m_input_system;
};

#endif /* COMPONENTS_INPUT_SELECT_CONTROL_H_ */
