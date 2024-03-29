/*
 * constant_control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_CONSTANT_CONTROL_H_
#define COMPONENTS_CONSTANT_CONTROL_H_

#include "../math_ext.h"

class ConstantControl
{
public:
	ConstantControl(const double move_decision, const double vertical_decision)
	: m_move_decision(clip(move_decision, -1.0, 1.0))
	, m_vertical_decision(clip(vertical_decision, -1.0, 1.0))
	{}

    template<typename ExtractorF>
	ConstantControl
	( ExtractorF&& extract
	)
	: ConstantControl
	  { extract()
	  , extract()
	  }
	{}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseConstantControl");
    	insert(m_move_decision);
    	insert(m_vertical_decision);
    }

    double decision_vertical() const { return m_vertical_decision; }
    bool decision_attack() const { return false; }
    double decision_walk() const { return m_move_decision; }
    ProcedureID attack_proc_id() const { return ProcedureID(0); }

    void set_decision_vertical(double val) { m_vertical_decision = clip(val, -1.0, 1.0); }
    void set_decision_attack(bool) {}
    void set_decision_walk(double val) { m_move_decision = clip(val, -1.0, 1.0); }
    void mod_decision_vertical(double val) { set_decision_vertical(m_vertical_decision+val); }
    void mod_decision_walk(double val) { set_decision_walk(m_move_decision+val); }
    void set_attack_proc_id(ProcedureID) {}

    void update_decisions(const Time) {}
    void clear_decisions()
    {
    	m_move_decision = 0;
    	m_vertical_decision = 0;
    }

private:
    double m_move_decision, m_vertical_decision;
};

#endif /* COMPONENTS_CONSTANT_CONTROL_H_ */
