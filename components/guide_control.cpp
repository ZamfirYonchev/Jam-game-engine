/*
 * guide_control.cpp
 *
 *  Created on: Dec 7, 2019
 *      Author: zamfi
 */

#include "guide_control.h"
#include "../globals.h"
#include "../math_ext.h"

void GuideControl::update_decisions(Time time_diff)
{
	if(entity_system().entity(m_target_id))
	{
		Position* position = entity_system().entity(m_target_id)->position();
		double distance_x = position->x() + position->w()/2.0 - position->x() - position->w()/2.0;
		double distance_y = position->y() + position->h()/2.0 - position->y() - position->h()/2.0;

		m_walk_dir = sign(distance_x) * (abs(distance_x) > m_attack_range);
		m_look_dir = distance_x > 0 ? RIGHT : distance_x < 0 ? LEFT : m_look_dir;

		m_jump = distance_y > 100 && distance_y < 200 && abs(distance_x) < 200;
	}
	else
	{
		//error m_target_id
	}
}




