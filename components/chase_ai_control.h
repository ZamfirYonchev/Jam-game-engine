/*
 * chase_ai_control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_CHASE_AI_CONTROL_H_
#define COMPONENTS_CHASE_AI_CONTROL_H_

#include "control_enums.h"
#include "../math_ext.h"
#include "../types.h"

template<typename PositionT>
class ChaseAIControl
{
public:
	ChaseAIControl
		(const EntityID target_id
	   , const ProcedureID attack_proc_id
	   , const int attack_cooldown
	   , const double attack_range
	   , const EntityID self_id
	   , ComponentAccess<const PositionT> position_accessor
	   )
	: m_target_id(target_id)
	, m_walk_dir(0)
	, m_attack(false)
	, m_attack_proc_id(attack_proc_id)
	, m_attack_cooldown(attack_cooldown)
	, m_current_attack_cooldown(0)
	, m_look_dir(LookDir::RIGHT)
	, m_attack_range(attack_range)
	, m_self_id(self_id)
	, m_position_accessor(std::move(position_accessor))
	{}

    template<typename ExtractorF, typename SelfIDObtainerF>
	ChaseAIControl
	( ExtractorF&& extract
	, const SelfIDObtainerF& obtain_self_id
	, ComponentAccess<const PositionT> position_accessor
	)
	: ChaseAIControl
	  { extract()
	  , extract()
	  , extract()
	  , extract()
	  , obtain_self_id()
	  , std::move(position_accessor)
	  }
	{}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseChaseAIControl");
    	insert(m_target_id);
    	insert(m_attack_proc_id);
    	insert(m_attack_cooldown);
    	insert(m_attack_range);
    }

    double decision_vertical() const { return 0; }
    bool decision_attack() const { return m_attack; }
    double decision_walk() const { return m_walk_dir; }
    ProcedureID attack_proc_id() const { return m_attack_proc_id; }
    LookDir look_dir() const { return m_look_dir; }

    void set_decision_vertical(double) {}
    void set_decision_attack(bool) {}
    void set_decision_walk(double) {}
    void mod_decision_vertical(double) {}
    void mod_decision_walk(double) {}
    void set_attack_proc_id(ProcedureID val) { m_attack_proc_id = val; }
    void set_look_dir(LookDir val) { m_look_dir = val; }

    void update_decisions(const Time time_diff)
    {
    	const auto& self_position = m_position_accessor(m_self_id);
    	const auto& target_position = m_position_accessor(m_target_id);

    	m_current_attack_cooldown = max(m_current_attack_cooldown-int(time_diff), 0);

    	if(target_position)
    	{
    		const double distance_x = target_position.x() - self_position.x() + (target_position.w() - self_position.w())/2.0;
    		const double distance_y = target_position.y() - self_position.y() + (target_position.h() - self_position.h())/2.0;

    		m_walk_dir = sign(distance_x) * (abs(distance_x) > m_attack_range);
    		m_look_dir = distance_x > 0 ? LookDir::RIGHT : distance_x < 0 ? LookDir::LEFT : m_look_dir;
    		m_attack = (m_attack_proc_id > 0) && (abs(distance_x) <= m_attack_range) && (abs(distance_y) <= 30) && (m_current_attack_cooldown == 0);

    		if(m_attack)
    			m_current_attack_cooldown = m_attack_cooldown;
    	}
    	else
    	{
    		//error m_target_id
    	}
    }

    void clear_decisions()
    {
        m_walk_dir = 0;
        m_attack = false;
    }

private:
    EntityID m_target_id;
    int8_t m_walk_dir;
    bool m_attack;
    ProcedureID m_attack_proc_id;
    int m_attack_cooldown;
    int m_current_attack_cooldown;
    LookDir m_look_dir;
    double m_attack_range;
    EntityID m_self_id;
    ComponentAccess<const PositionT> m_position_accessor;
};


#endif /* COMPONENTS_CHASE_AI_CONTROL_H_ */
