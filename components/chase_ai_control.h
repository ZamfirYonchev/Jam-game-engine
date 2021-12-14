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
#include <functional>
#include <ostream>
#include "../types.h"
#include "../command_value.h"

class Position;

class ChaseAIControl
{
public:
	ChaseAIControl
		(const EntityID self_id
	   , const EntityID target_id
	   , const ProcedureID attack_proc_id
	   , const int attack_cooldown
	   , const double attack_range
	   , ComponentAccess<const Position> position_accessor
	   )
	: m_self_id(self_id)
	, m_target_id(target_id)
	, m_walk_dir(0)
	, m_attack(false)
	, m_attack_proc_id(attack_proc_id)
	, m_attack_cooldown(attack_cooldown)
	, m_current_attack_cooldown(0)
	, m_look_dir(LookDir::RIGHT)
	, m_attack_range(attack_range)
	, m_position_accessor(std::move(position_accessor))
	{}

    template<typename ExtractorF>
	ChaseAIControl
	( ExtractorF&& extract
	, const CommandValue& self_id
	, const ComponentAccess<const Position>& position_accessor
	)
	: ChaseAIControl
	  { EntityID(self_id.integer())
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().real()
	  , position_accessor
	  }
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

    void set_decision_vertical(double) {}
    void set_decision_attack(bool) {}
    void set_decision_walk(double) {}
    void mod_decision_vertical(double) {}
    void mod_decision_walk(double) {}
    void set_attack_proc_id(ProcedureID val) { m_attack_proc_id = val; }
    void set_look_dir(LookDir val) { m_look_dir = val; }

    void update_decisions(const Time time_diff);
    void clear_decisions()
    {
        m_walk_dir = 0;
        m_attack = false;
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
    ComponentAccess<const Position> m_position_accessor;
};


#endif /* COMPONENTS_CHASE_AI_CONTROL_H_ */
