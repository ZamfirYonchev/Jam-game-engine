/*
 * null_control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_CONTROL_H_
#define COMPONENTS_NULL_CONTROL_H_

#include "control.h"

class NullControl : public Control
{
public:
	using Base = Control;
    void print(std::ostream& to) const
    {
    	to << "UseNullControl ";
    }

    double decision_jump() const { return 0.0; }
    double decision_duck() const { return 0.0; }
    bool decision_attack() const { return false; }
    double decision_walk() const { return 0.0; }
    ProcedureID attack_proc_id() const { return ProcedureID{-1}; }
    LookDir look_dir() const { return LookDir::RIGHT; }

    void set_decision_jump(double val) {}
    void set_decision_duck(double val) {}
    void set_decision_attack(bool val) {}
    void set_decision_walk(double val) {}
    void set_attack_proc_id(ProcedureID val) {}
    void set_look_dir(LookDir val) {}

    void update_decisions(const Time time) {}
    void clear_decisions() {}
};

#endif /* COMPONENTS_NULL_CONTROL_H_ */
