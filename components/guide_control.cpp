/*
 * guide_control.cpp
 *
 *  Created on: Dec 7, 2019
 *      Author: zamfi
 */

#include "guide_control.h"
#include "../math_ext.h"
#include "../systems/entity_system.h"
#include "../systems/systems.h"

void GuideControl::update_decisions(const Time time_diff)
{
	const auto& target_position = system<EntitySystem>().entity_component<Position>(m_target_id);

	if(target_position)
	{
		const auto& self_position = system<EntitySystem>().entity_component<Position>(m_self_id);
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




