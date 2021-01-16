/*
 * chase_ai_control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_CHASE_AI_CONTROL_H_
#define COMPONENTS_CHASE_AI_CONTROL_H_

#include "control.h"
#include "../math_ext.h"
#include "position.h"

template<typename EntitySystemT>
class ChaseAIControl : public Control
{
public:
	using Base = Control;
	ChaseAIControl(EntityID self_id, EntityID target_id, ProcedureID attack_proc_id, double attack_cooldown, double attack_range, EntitySystemT& entity_system)
	: m_self_id(self_id)
	, m_target_id(target_id)
	, m_walk_dir(0)
	, m_attack(false)
	, m_attack_proc_id(attack_proc_id)
	, m_attack_cooldown(attack_cooldown)
	, m_current_attack_cooldown(0)
	, m_look_dir(LookDir::RIGHT)
	, m_attack_range(attack_range)
	, m_entity_system(entity_system)
	{}

    void print(std::ostream& to) const
    {
    	to << "UseChaseAIControl "
    	   << m_target_id << " "
    	   << m_attack_proc_id << " "
    	   << m_attack_cooldown << " "
    	   << m_attack_range << " ";
    }

    double decision_vertical() const { return 0; }
    bool decision_attack() const { return m_attack; }
    double decision_walk() const { return m_walk_dir; }
    ProcedureID attack_proc_id() const { return m_attack_proc_id; }
    LookDir look_dir() const { return m_look_dir; }

    void set_decision_vertical(double val) {}
    void set_decision_attack(bool val) {}
    void set_decision_walk(double val) {}
    void mod_decision_vertical(double val) {}
    void mod_decision_walk(double val) {}
    void set_attack_proc_id(ProcedureID val) { m_attack_proc_id = val; }
    void set_look_dir(LookDir val) { m_look_dir = val; }

    void update_decisions(const Time time_diff)
    {
    	m_current_attack_cooldown = max(m_current_attack_cooldown-time_diff, 0);

    	const auto& target_position = m_entity_system.entity_component(m_target_id, Position::null);

    	if(target_position)
    	{
    		const auto& self_position = m_entity_system.entity_component(m_self_id, Position::null);
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
        m_walk_dir = 0.0;
        m_attack = 0.0;
    }

    EntityID m_self_id, m_target_id;

private:
    int8_t m_walk_dir;
    bool m_attack;
    ProcedureID m_attack_proc_id;
    int m_attack_cooldown;
    int m_current_attack_cooldown;
    LookDir m_look_dir;
    double m_attack_range;
    EntitySystemT& m_entity_system;
};


#endif /* COMPONENTS_CHASE_AI_CONTROL_H_ */
