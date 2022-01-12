/*
 * input_control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_INPUT_CONTROL_H_
#define COMPONENTS_INPUT_CONTROL_H_

#include "control_enums.h"
#include "../math_ext.h"
#include "../types.h"
#include "../systems/input_system.h"

template<typename MovementT>
class InputControl
{
public:
	InputControl
		(const ProcedureID shoot_proc_id
	   , const int shoot_cooldown
	   , const bool stability_control
	   , const InputSystem& input_system
	   , const EntityID self_id
	   , ComponentAccess<const MovementT> movement_accessor
	   )
    : m_self_id(self_id)
	, m_walk_dir(0)
    , m_vertical_dir(0)
    , m_shoot(false)
    , m_shoot_proc_id(shoot_proc_id)
    , m_shoot_cooldown(shoot_cooldown)
	, m_current_shoot_cooldown(shoot_cooldown)
	, m_look_dir(LookDir::RIGHT)
	, m_stability_control(stability_control)
	, m_input_system(input_system)
	, m_movement_accessor{std::move(movement_accessor)}
    {}

    template<typename ExtractorF, typename SelfIDObtainerF>
	InputControl
	( ExtractorF&& extract
	, const InputSystem& input_system
	, const SelfIDObtainerF& obtain_self_id
	, ComponentAccess<const MovementT> movement_accessor
	)
	: InputControl
	  { extract()
	  , extract()
	  , extract()
	  , input_system
	  , obtain_self_id()
	  , std::move(movement_accessor)
	  }
    {}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseInputControl");
    	insert(m_shoot_proc_id);
    	insert(m_shoot_cooldown);
    	insert(m_stability_control);
    }

    double decision_vertical() const { return m_vertical_dir; }
    bool decision_attack() const { return m_shoot; }
    double decision_walk() const { return m_walk_dir; }
    ProcedureID attack_proc_id() const { return m_shoot_proc_id; }
    LookDir look_dir() const { return m_look_dir; }

    void set_decision_vertical(double val) { m_vertical_dir = clip(val, -1.0, 1.0); }
    void set_decision_attack(bool val) { m_shoot = val; }
    void set_decision_walk(double val) { m_walk_dir = clip(val, -1.0, 1.0); }
    void mod_decision_vertical(double val) { set_decision_vertical(m_vertical_dir+val); }
    void mod_decision_walk(double val) { set_decision_walk(m_walk_dir+val); }
    void set_attack_proc_id(ProcedureID val) { m_shoot_proc_id = val; }
    void set_look_dir(LookDir val) { m_look_dir = val; }

    void update_decisions(const Time time_diff)
    {
    	const auto& movement = m_movement_accessor(m_self_id);
    	m_current_shoot_cooldown = max(m_current_shoot_cooldown-int(time_diff), 0);

    	m_vertical_dir = m_input_system.get().jumping() - m_input_system.get().ducking();
    	m_walk_dir = m_input_system.get().going_right() - m_input_system.get().going_left();

    	m_look_dir = m_walk_dir > 0 ? LookDir::RIGHT : m_walk_dir < 0 ? LookDir::LEFT : m_look_dir;

    	if(m_stability_control && m_walk_dir == 0 && abs(movement.vx()) > movement.move_force()/movement.mass())
    	{
    		m_walk_dir = -sign(movement.vx());
    	}

    	m_shoot = m_input_system.get().shooting() && (m_current_shoot_cooldown == 0);

    	if(m_shoot)
    		m_current_shoot_cooldown = m_shoot_cooldown;
    }

    void clear_decisions()
    {
        m_vertical_dir = 0.0;
        m_shoot = false;
        m_walk_dir = 0.0;
    }

    EntityID m_self_id;

private:
    double m_walk_dir, m_vertical_dir;
    bool m_shoot;
    ProcedureID m_shoot_proc_id;
    int m_shoot_cooldown;
    int m_current_shoot_cooldown;
    LookDir m_look_dir;
    bool m_stability_control;
    std::reference_wrapper<const InputSystem> m_input_system;
    ComponentAccess<const MovementT> m_movement_accessor;
};


#endif /* COMPONENTS_INPUT_CONTROL_H_ */
