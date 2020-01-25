/*
 * input_control.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "input_control.h"
#include "../math_ext.h"
#include <iostream>

void InputControl::update_decisions(int32_t time_diff)
{
	m_current_shoot_cooldown = max(m_current_shoot_cooldown-time_diff, 0);

    m_jump = m_input->jumping() && !m_input->ducking();
    m_duck = m_input->ducking();
    m_walk_dir = m_input->going_right() - m_input->going_left();
	m_look_dir = m_walk_dir > 0 ? RIGHT : m_walk_dir < 0 ? LEFT : m_look_dir;
    m_shoot = m_input->shooting() && (m_current_shoot_cooldown == 0);

    if(m_shoot)
    	m_current_shoot_cooldown = m_shoot_cooldown;
}
