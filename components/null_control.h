/*
 * null_control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_CONTROL_H_
#define COMPONENTS_NULL_CONTROL_H_

class NullControl
{
public:

	template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseNullControl");
    }

    double decision_vertical() const { return 0.0; }
    bool decision_attack() const { return false; }
    double decision_walk() const { return 0.0; }
    ProcedureID attack_proc_id() const { return ProcedureID(0); }

    void set_decision_vertical(double) {}
    void set_decision_attack(bool) {}
    void set_decision_walk(double) {}
    void mod_decision_vertical(double) {}
    void mod_decision_walk(double) {}
    void set_attack_proc_id(ProcedureID) {}

    void update_decisions(const Time) {}
    void clear_decisions() {}
};

#endif /* COMPONENTS_NULL_CONTROL_H_ */
