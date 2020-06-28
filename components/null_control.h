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
    void print(std::ostream& to) const
    {
    	to << "UseNullControl ";
    }

    bool decision_jump() const { return false; }
    bool decision_duck() const { return false; }
    bool decision_attack() const { return false; }
    int8_t decision_walk() const { return 0; }
    ProcedureID attack_proc_id() const { return -1; }
    LookDir look_dir() const { return RIGHT; }

    void set_decision_jump(bool val) {}
    void set_decision_duck(bool val) {}
    void set_decision_attack(bool val) {}
    void set_decision_walk(int8_t val) {}
    void set_attack_proc_id(ProcedureID val) {}
    void set_look_dir(LookDir val) {}

    void update_decisions(Time time) {}
    void clear_decisions() {}
};

#endif /* COMPONENTS_NULL_CONTROL_H_ */
