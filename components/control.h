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
#include <ostream>

class NullControl;

class Control
{
public:
	using Null = NullControl;
    enum LookDir {RIGHT = 0, LEFT = 1};
    virtual ~Control() {}
    virtual void print(std::ostream& to) const = 0;

    virtual double decision_jump() const = 0;
    virtual double decision_duck() const = 0;
    virtual bool decision_attack() const = 0;
    virtual double decision_walk() const = 0;
    virtual ProcedureID attack_proc_id() const = 0;
    virtual LookDir look_dir() const = 0;

    virtual void set_decision_jump(double val) = 0;
    virtual void set_decision_duck(double val) = 0;
    virtual void set_decision_attack(bool val) = 0;
    virtual void set_decision_walk(double val) = 0;
    virtual void set_attack_proc_id(ProcedureID val) = 0;
    virtual void set_look_dir(LookDir val) = 0;

    virtual void update_decisions(const Time time) = 0;
    virtual void clear_decisions() = 0;

    static Control* null;

    friend std::ostream& operator<< (std::ostream& out, const Control& component)
    {
    	component.print(out);
        out << std::endl;
        return out;
    }
};


#endif /* COMPONENTS_CONTROL_H_ */
