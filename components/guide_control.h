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
#include "position.h"

template<typename EntitySystemT>
class GuideControl : public Control
{
public:
	using Base = Control;
	GuideControl(AbsEntityID self_id, EntityID target_id, double range, EntitySystemT& entity_system)
	: m_self_id(self_id)
	, m_target_id(target_id)
	, m_walk_dir(0)
	, m_jump(false)
	, m_duck(false)
	, m_look_dir(RIGHT)
	, m_range(range)
	, m_entity_system(entity_system)
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

    void update_decisions(const Time time_diff)
    {
    	const auto& target_position = m_entity_system.entity_component(m_target_id, (Position*)nullptr);

    	if(target_position)
    	{
    		const auto& self_position = m_entity_system.entity_component(m_self_id, (Position*)nullptr);
    		const double distance_x = target_position.x() - self_position.x() + (target_position.w() - self_position.w())/2.0;
    		const double distance_y = target_position.y() - self_position.y() + (target_position.h() - self_position.h())/2.0;

    		m_walk_dir = sign(distance_x) * (abs(distance_x) > m_range);
    		m_look_dir = distance_x > 0 ? RIGHT : distance_x < 0 ? LEFT : m_look_dir;

    		m_jump = distance_y > 100 && distance_y < 200 && abs(distance_x) < 200;
    	}
    	else
    	{
    		//error m_target_id
    	}
    }

    void clear_decisions()
    {
        m_walk_dir = 0.0;
        m_jump = 0.0;
        m_duck = 0.0;
    }

    AbsEntityID m_self_id;
	EntityID m_target_id;

private:
    double m_walk_dir, m_jump, m_duck;
    LookDir m_look_dir;
    double m_range;
    EntitySystemT& m_entity_system;
};



#endif /* COMPONENTS_GUIDE_CONTROL_H_ */
