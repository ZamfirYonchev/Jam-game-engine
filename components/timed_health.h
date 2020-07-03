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
	using Base = Health;
    TimedHealth(double ttl, ProcedureID proc_id)
	: m_time_to_live(ttl)
	, m_max_ttl(ttl)
	, m_ttl_change(0.0)
	, m_proc_id(proc_id)
	{}

    void print(std::ostream& to) const
    {
    	to << "UseTimedHealth "
    	   << m_time_to_live << " "
    	   << m_proc_id << " ";
    }

    void set_max_hp(double hp) { m_max_ttl = hp; }
    void set_hp(double hp) { m_time_to_live = hp; }
    void set_hp_change(double hp_change) { m_ttl_change = hp_change; }
    void mod_hp_change(double hp_change) { m_ttl_change += hp_change; }
    void update_health(double time_diff)
    {
    	m_time_to_live = clip(m_time_to_live+m_ttl_change-time_diff, 0.0, m_max_ttl);
    	m_ttl_change = 0;
    }

    double hp() const { return m_time_to_live; }
    double max_hp() const { return m_max_ttl; }
    bool alive() const { return m_time_to_live > 0; }
    ProcedureID on_death_exec() const { return m_proc_id; }
    void set_on_death_exec(ProcedureID val) { m_proc_id = val; }
    bool stunned() const { return false; }

private:
    double m_time_to_live;
    double m_max_ttl;
    double m_ttl_change;
    ProcedureID m_proc_id;
};

#endif /* COMPONENTS_TIMED_HEALTH_H_ */
