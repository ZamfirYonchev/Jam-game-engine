/*
 * character_health.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_CHARACTER_HEALTH_H_
#define COMPONENTS_CHARACTER_HEALTH_H_

#include "../math_ext.h"
#include "../types.h"

class CharacterHealth
{
public:
	constexpr static int STUN_TIME = 100;
    CharacterHealth(const double hp, const double max_hp)
	: m_max_hit_points(max_hp)
	, m_stun_cnt(0)
	, m_proc_id{ProcedureID{0}}
	{ set_hp(hp); }

    template<typename ExtractorF>
    CharacterHealth
	( ExtractorF&& extract
	)
	: CharacterHealth
	  { extract()
	  , extract()
	  }
	{}

    CharacterHealth() : CharacterHealth(0, 0) {}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseCharacterHealth");
    	insert(m_hit_points);
    	insert(m_max_hit_points);
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

    void mod_hp(double hp_change)
    {
        set_hp(m_hit_points + hp_change);

        if(hp_change < 0.0) m_stun_cnt = STUN_TIME;
    }

    void update_health(const Time time_diff)
    {
		m_stun_cnt = max(m_stun_cnt - int(time_diff), 0);
    }

    double hp() const { return m_hit_points; }
    double max_hp() const { return m_max_hit_points; }
    bool alive() const { return m_hit_points > 0; }
    ProcedureID on_death_exec() const { return m_proc_id; }
    void set_on_death_exec(const ProcedureID id) { m_proc_id = id; }
    bool stunned() const { return m_stun_cnt > 0; }

private:
    double m_hit_points, m_max_hit_points;
	int m_stun_cnt;
	ProcedureID m_proc_id;
};

#endif /* COMPONENTS_CHARACTER_HEALTH_H_ */
