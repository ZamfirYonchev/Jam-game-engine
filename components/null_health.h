/*
 * null_health.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_HEALTH_H_
#define COMPONENTS_NULL_HEALTH_H_

#include "health.h"

class NullHealth : public Health
{
public:
    void set_max_hp(double hp) {}
    void set_hp(double hp) {}
    void set_hp_change(double hp_change) {}
    void mod_hp_change(double hp_change) {}
    void update_health(double time_diff) {}
    double hp() const { return 0; }
    double max_hp() const { return 0; }
    bool alive() const { return true; }
    ProcedureID on_death_exec() const { return -1; }
    void set_on_death_exec(ProcedureID proc_id) {}
    bool stunned() const { return false; }
};

#endif /* COMPONENTS_NULL_HEALTH_H_ */
