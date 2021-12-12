/*
 * input_control.cpp
 *
 *  Created on: Dec 4, 2021
 *      Author: zamfi
 */

#include "input_control.h"
#include "movement.h"

void InputControl::update_decisions(const Time time_diff)
{
	const Movement& movement = m_movement_accessor(m_self_id);
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
