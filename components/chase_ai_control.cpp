/*
 * chase_ai_control.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#include "chase_ai_control.h"
#include "../math_ext.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

void ChaseAIControl::update_decisions(const Time time_diff)
{
	m_current_attack_cooldown = max(m_current_attack_cooldown-time_diff, 0);

	const auto& target_position = system<EntitySystem>().entity_component<Position>(m_target_id);

	if(target_position)
	{
		const auto& self_position = system<EntitySystem>().entity_component<Position>(m_self_id);
		const double distance_x = target_position.x() - self_position.x() + (target_position.w() - self_position.w())/2.0;
		const double distance_y = target_position.y() - self_position.y() + (target_position.h() - self_position.h())/2.0;

		m_walk_dir = sign(distance_x) * (abs(distance_x) > m_attack_range);
		m_look_dir = distance_x > 0 ? RIGHT : distance_x < 0 ? LEFT : m_look_dir;
		m_attack = (m_attack_proc_id >= 0) && (abs(distance_x) <= m_attack_range) && (abs(distance_y) <= 30) && (m_current_attack_cooldown == 0);

		if(m_attack)
			m_current_attack_cooldown = m_attack_cooldown;
	}
	else
	{
		//error m_target_id
	}
}

