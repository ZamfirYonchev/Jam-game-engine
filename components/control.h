/*
 * control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_CONTROL_H_
#define COMPONENTS_CONTROL_H_

#include <cinttypes>
#include "../types.h"

class Control
{
public:
    enum LookDir {RIGHT = 0, LEFT = 1};
    virtual ~Control() {}

    virtual bool decision_jump() const = 0;
    virtual bool decision_duck() const = 0;
    virtual bool decision_attack() const = 0;
    virtual int8_t decision_walk() const = 0;
    virtual ProcedureID attack_proc_id() const = 0;
    virtual LookDir look_dir() const = 0;

    virtual void set_decision_jump(bool val) = 0;
    virtual void set_decision_duck(bool val) = 0;
    virtual void set_decision_attack(bool val) = 0;
    virtual void set_decision_walk(int8_t val) = 0;
    virtual void set_attack_proc_id(ProcedureID val) = 0;
    virtual void set_look_dir(LookDir val) = 0;

    virtual void update_decisions(Time time) = 0;
    virtual void clear_decisions() = 0;

    static Control* null;
};


#endif /* COMPONENTS_CONTROL_H_ */
