/*
 * guide_control.h
 *
 *  Created on: Dec 7, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_GUIDE_CONTROL_H_
#define COMPONENTS_GUIDE_CONTROL_H_

#include "control.h"
#include "../math_ext.h"

class GuideControl : public Control
{
public:
	using Base = Control;
	GuideControl(EntityID self_id, EntityID target_id, double range)
	: m_walk_dir(0)
	, m_jump(false)
	, m_duck(false)
	, m_self_id(self_id)
	, m_target_id(target_id)
	, m_look_dir(RIGHT)
	, m_range(range)
	{}

    void print(std::ostream& to) const
    {
    	to << "UseGuideControl "
    	   << m_target_id << " "
    	   << m_range << " ";
    }

    double decision_jump() const { return m_jump; }
    double decision_duck() const { return m_duck; }
    bool decision_attack() const { return false; }
    double decision_walk() const { return m_walk_dir; }
    ProcedureID attack_proc_id() const { return ProcedureID{-1}; }
    LookDir look_dir() const { return m_look_dir; }

    void set_decision_jump(double val) { m_jump = clip(val, 0.0, 1.0); }
    void set_decision_duck(double val) { m_duck = clip(val, 0.0, 1.0); }
    void set_decision_attack(bool val) {}
    void set_decision_walk(double val) { m_walk_dir = clip(val, -1.0, 1.0); }
    void set_attack_proc_id(ProcedureID val) {}
    void set_look_dir(LookDir val) { m_look_dir = val; }

    void update_decisions(const Time time_diff);
    void clear_decisions()
    {
        m_walk_dir = 0.0;
        m_jump = 0.0;
        m_duck = 0.0;
    }

private:
    double m_walk_dir, m_jump, m_duck;
    EntityID m_self_id, m_target_id;
    LookDir m_look_dir;
    double m_range;
};



#endif /* COMPONENTS_GUIDE_CONTROL_H_ */
