/*
 * timed_health.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_TIMED_HEALTH_H_
#define COMPONENTS_TIMED_HEALTH_H_

#include "health.h"
#include "../math_ext.h"

class TimedHealth : public Health
{
public:
    TimedHealth(double ttl, ProcedureID proc_id)
	: m_time_to_live(ttl)
	, m_proc_id(proc_id)
	{}

    void set_max_hp(double hp) {}
    void set_hp(double hp) { m_time_to_live = hp; }
    void set_hp_change(double hp_change) {}
    void mod_hp_change(double hp_change) {}
    void update_health(double time_diff) { m_time_to_live = max(m_time_to_live-time_diff, 0.0); }
    double hp() const { return m_time_to_live; }
    double max_hp() const { return 0; }
    bool alive() const { return m_time_to_live > 0; }
    ProcedureID on_death_exec() const { return m_proc_id; }
    void set_on_death_exec(ProcedureID val) { m_proc_id = val; }
    bool stunned() const { return false; }

private:
    double m_time_to_live;
    ProcedureID m_proc_id;
};

#endif /* COMPONENTS_TIMED_HEALTH_H_ */
