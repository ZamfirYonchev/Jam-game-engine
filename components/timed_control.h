/*
 * timed_control.h
 *
 *  Created on: Jan 27, 2021
 *      Author: zamfi
 */

#ifndef COMPONENTS_TIMED_CONTROL_H_
#define COMPONENTS_TIMED_CONTROL_H_

#include "control_enums.h"
#include "../math_ext.h"

class TimedControl
{
public:
	TimedControl
		(const int max_duration
	   , const int repeats
	   , const double horizontal
	   , const double vertical
	   , const ProcedureID proc_id
		)
	: m_max_duration{max_duration}
	, m_current_duration{0}
	, m_proc_id{proc_id}
	, m_horizontal{horizontal}
	, m_vertical{vertical}
	, m_attack{false}
	, m_repeats{repeats}
	, m_walk{1}
	{}

    template<typename ExtractorF>
	TimedControl
	( ExtractorF&& extract
	)
	: TimedControl
	  { extract().integer()
	  , extract().integer()
	  , extract().real()
	  , extract().real()
	  , extract().integer()
	  }
	{}

    void print(std::ostream& to) const
    {
    	to << "UseTimedControl "
    	   << m_max_duration << " "
    	   << m_repeats << " ";
    }

    double decision_vertical() const { return m_walk * m_vertical; }
    bool decision_attack() const { return m_attack; }
    double decision_walk() const { return m_walk * m_horizontal; }
    ProcedureID attack_proc_id() const { return m_proc_id; }
    LookDir look_dir() const { return m_walk < 0 ? LookDir::LEFT : LookDir::RIGHT; }

    void set_decision_vertical(double val) {}
    void set_decision_attack(bool val) {}
    void set_decision_walk(double val) {}
    void mod_decision_vertical(double val) {}
    void mod_decision_walk(double val) {}
    void set_attack_proc_id(ProcedureID val) { m_proc_id = val; }
    void set_look_dir(LookDir val) {}

    void update_decisions(const Time time_diff)
    {
		m_current_duration += time_diff*(m_repeats != 0);
		m_repeats -= (m_repeats > 0)*(m_current_duration >= m_max_duration);
		m_walk *= (1 - 2*(m_current_duration >= m_max_duration))*(m_repeats != 0);
		m_attack = m_current_duration >= m_max_duration;
		m_current_duration *= (m_current_duration < m_max_duration);
    }

    void clear_decisions()
    {
        m_walk = 0;
        m_attack = false;
    }

private:
    int m_max_duration;
    int m_current_duration;
    ProcedureID m_proc_id;
    double m_horizontal;
    double m_vertical;
    bool m_attack;
    int m_repeats;
    int8_t m_walk;
};

#endif /* COMPONENTS_TIMED_CONTROL_H_ */
