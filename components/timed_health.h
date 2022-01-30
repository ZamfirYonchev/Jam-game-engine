/*
 * timed_health.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_TIMED_HEALTH_H_
#define COMPONENTS_TIMED_HEALTH_H_

#include "../types.h"
#include "../math_ext.h"

class TimedHealth
{
public:
    TimedHealth(const double ttl, const ProcedureID proc_id)
	: m_time_to_live{abs(ttl)}
	, m_max_ttl{abs(ttl)}
	, m_proc_id{proc_id}
	, count_down{ttl >= 0}
	{}

    template<typename ExtractorF>
    TimedHealth
	( ExtractorF&& extract
	)
	: TimedHealth
	  { extract()
	  , extract()
	  }
	{}

	template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseTimedHealth");
    	insert(m_time_to_live * (count_down ? 1 : -1));
    	insert(m_proc_id);
    }

    void set_max_hp(double hp) { m_max_ttl = hp; }
    void set_hp(double hp) { m_time_to_live = clip(hp, 0.0, m_max_ttl); }
    void mod_hp(double hp_change) { set_hp(m_time_to_live+hp_change); }
    void update_health(const Time time_diff)
    {
    	set_hp(m_time_to_live-time_diff);
    }

    double hp() const { return count_down ? m_time_to_live : m_max_ttl-m_time_to_live; }
    double max_hp() const { return m_max_ttl; }
    bool alive() const { return m_time_to_live > 0; }
    ProcedureID on_death_exec() const { return m_proc_id; }
    void set_on_death_exec(ProcedureID val) { m_proc_id = val; }
    bool stunned() const { return false; }

private:
    double m_time_to_live;
    double m_max_ttl;
    ProcedureID m_proc_id;
    bool count_down;
};

#endif /* COMPONENTS_TIMED_HEALTH_H_ */
