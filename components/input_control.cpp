/*
 * input_control.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "input_control.h"
#include "../math_ext.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"
#include "../systems/input_system.h"

void InputControl::update_decisions(const Time time_diff)
{
	const InputSystem& input = system<InputSystem>();
	m_current_shoot_cooldown = max(m_current_shoot_cooldown-time_diff, 0);

    m_jump = input.jumping() && !input.ducking();
    m_duck = input.ducking();
    m_walk_dir = input.going_right() - input.going_left();

	m_look_dir = m_walk_dir > 0 ? RIGHT : m_walk_dir < 0 ? LEFT : m_look_dir;

	const auto& self_movement = system<EntitySystem>().entity_component<Movement>(m_self_id);

	if(m_stability_control && m_walk_dir == 0 && abs(self_movement.vx()) > self_movement.move_force()/self_movement.mass())
    {
    	m_walk_dir = -sign(self_movement.vx());
    }

    m_shoot = input.shooting() && (m_current_shoot_cooldown == 0);

    if(m_shoot)
    	m_current_shoot_cooldown = m_shoot_cooldown;
}
