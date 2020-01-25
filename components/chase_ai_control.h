/*
 * chase_ai_control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_CHASE_AI_CONTROL_H_
#define COMPONENTS_CHASE_AI_CONTROL_H_

#include "control.h"

class ChaseAIControl : public Control
{
public:
	ChaseAIControl(EntityID self_id, EntityID target_id, ProcedureID attack_proc_id, double attack_cooldown, double attack_range)
	: m_walk_dir(0)
	, m_attack(false)
	, m_attack_proc_id(attack_proc_id)
	, m_attack_cooldown(attack_cooldown)
	, m_current_attack_cooldown(0)
	, m_self_id(self_id)
	, m_target_id(target_id)
	, m_look_dir(RIGHT)
	, m_attack_range(attack_range)
	{}

    bool decision_jump() const { return false; }
    bool decision_duck() const { return false; }
    bool decision_attack() const { return m_attack; }
    int8_t decision_walk() const { return m_walk_dir; }
    ProcedureID attack_proc_id() const { return m_attack_proc_id; }
    LookDir look_dir() const { return m_look_dir; }

    void set_decision_jump(bool val) {}
    void set_decision_duck(bool val) {}
    void set_decision_attack(bool val) { m_attack = val; }
    void set_decision_walk(int8_t val) { m_walk_dir = val; }
    void set_attack_proc_id(ProcedureID val) { m_attack_proc_id = val; }
    void set_look_dir(LookDir val) { m_look_dir = val; }

    void update_decisions(Time time_diff);
    void clear_decisions()
    {
        m_walk_dir = 0;
        m_attack = false;
    }

private:
    int8_t m_walk_dir;
    bool m_attack;
    ProcedureID m_attack_proc_id;
    int m_attack_cooldown;
    int m_current_attack_cooldown;
    EntityID m_self_id, m_target_id;
    LookDir m_look_dir;
    double m_attack_range;
};


#endif /* COMPONENTS_CHASE_AI_CONTROL_H_ */
