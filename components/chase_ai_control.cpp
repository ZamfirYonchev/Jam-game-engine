/*
 * chase_ai_control.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#include "chase_ai_control.h"
#include "../globals.h"
#include "../math_ext.h"
#include <iostream>

void ChaseAIControl::update_decisions(Time time_diff)
{
	m_current_attack_cooldown = max(m_current_attack_cooldown-time_diff, 0);
	try
	{
		double distance_x = globals.entity_system.entity(m_target_id).position()->x() + globals.entity_system.entity(m_target_id).position()->w()/2.0 - globals.entity_system.entity(m_self_id).position()->x() - globals.entity_system.entity(m_self_id).position()->w()/2.0;
		double distance_y = globals.entity_system.entity(m_target_id).position()->y() + globals.entity_system.entity(m_target_id).position()->h()/2.0 - globals.entity_system.entity(m_self_id).position()->y() - globals.entity_system.entity(m_self_id).position()->h()/2.0;

		m_walk_dir = sign(distance_x) * (abs(distance_x) > m_attack_range);
		m_look_dir = distance_x > 0 ? RIGHT : distance_x < 0 ? LEFT : m_look_dir;
		m_attack = (m_attack_proc_id >= 0) && (abs(distance_x) <= m_attack_range) && (abs(distance_y) <= 30) && (m_current_attack_cooldown == 0);

		if(m_attack)
			m_current_attack_cooldown = m_attack_cooldown;
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}

