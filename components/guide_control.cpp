/*
 * guide_control.cpp
 *
 *  Created on: Dec 3, 2021
 *      Author: zamfi
 */

#include "guide_control.h"
#include "position.h"

void GuideControl::update_decisions(const Time)
{
	const Position& self_position = m_position_accessor(m_self_id);
	const Position& target_position = m_position_accessor(m_target_id);

	if(target_position)
	{
		const double distance_x = target_position.x() - self_position.x() + (target_position.w() - self_position.w())/2.0;
		const double distance_y = target_position.y() - self_position.y() + (target_position.h() - self_position.h())/2.0;

		m_walk_dir = sign(distance_x) * (abs(distance_x) > m_range);
		m_look_dir = distance_x > 0 ? LookDir::RIGHT : distance_x < 0 ? LookDir::LEFT : m_look_dir;

		m_vertical = distance_y > 100 && distance_y < 200 && abs(distance_x) < 200;
	}
	else
	{
		//error m_target_id
	}
}
