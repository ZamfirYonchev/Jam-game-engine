/*
 * character_health.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_CHARACTER_HEALTH_H_
#define COMPONENTS_CHARACTER_HEALTH_H_

#include <ostream>
#include "../math_ext.h"
#include "../types.h"
#include "../command_value.h"

class CharacterHealth
{
public:
	constexpr static int STUN_TIME = 100;
    CharacterHealth(const double hp, const double max_hp)
	: m_max_hit_points(max_hp)
	, m_hp_change(0)
	, m_stun_cnt(0)
	{ set_hp(hp); }

    template<typename ExtractorF>
    CharacterHealth
	( ExtractorF&& extract
	)
	: CharacterHealth
	  { extract().real()
	  , extract().real()
	  }
	{}

    CharacterHealth() : CharacterHealth(0, 0) {}

    void print(std::ostream& to) const
    {
    	to << "UseCharacterHealth "
    	   << m_hit_points << " "
		   << m_max_hit_points << " ";
    }

    void set_max_hp(double hp)
    {
        m_max_hit_points = hp;
        m_hit_points = clip(m_hit_points, 0.0, m_max_hit_points);
    }

    void set_hp(double hp)
    {
        m_hit_points = clip(hp, 0.0, m_max_hit_points);
    }

    void set_hp_change(double hp_change)
    {
        m_hp_change = hp_change;
    }

    void mod_hp_change(double hp_change)
    {
        m_hp_change += hp_change;
    }

    void update_health(const Time time_diff)
    {
    	if(m_hp_change < 0) //hit
    		m_stun_cnt = STUN_TIME;
    	else
    		m_stun_cnt = max(m_stun_cnt - int(time_diff), 0);

        m_hit_points = clip(m_hit_points + m_hp_change, 0.0, m_max_hit_points);
        m_hp_change = 0;
    }

    double hp() const { return m_hit_points; }
    double max_hp() const { return m_max_hit_points; }
    bool alive() const { return m_hit_points > 0; }
    ProcedureID on_death_exec() const { return ProcedureID(0); }
    void set_on_death_exec(ProcedureID proc_id) {}
    bool stunned() const { return m_stun_cnt > 0; }

private:
    double m_hit_points, m_max_hit_points, m_hp_change;
	int m_stun_cnt;
};

#endif /* COMPONENTS_CHARACTER_HEALTH_H_ */
