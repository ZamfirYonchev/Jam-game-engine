/*
 * health.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_HEALTH_H_
#define COMPONENTS_HEALTH_H_

#include "../types.h"
#include <ostream>

class NullHealth;

class Health
{
public:
	using Null = NullHealth;
    virtual ~Health() {}
    virtual void print(std::ostream& to) const = 0;

    virtual double hp() const = 0;
    virtual double max_hp() const = 0;
    virtual bool alive() const = 0;
    virtual ProcedureID on_death_exec() const = 0;
    virtual bool stunned() const = 0;

    virtual void set_max_hp(double hp) = 0;
    virtual void set_hp(double hp) = 0;
    virtual void set_hp_change(double hp_change) = 0;
    virtual void set_on_death_exec(ProcedureID proc_id) = 0;

    virtual void mod_hp_change(double hp_change) = 0;

    virtual void update_health(double time_diff) = 0;

    static Health* null;

    friend std::ostream& operator<< (std::ostream& out, const Health& component)
    {
    	component.print(out);
        out << std::endl;
        return out;
    }
};

#endif /* COMPONENTS_HEALTH_H_ */
