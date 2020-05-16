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
	double distance_x = entity_system().entity(m_target_id)->position()->x() + entity_system().entity(m_target_id)->position()->w()/2.0 - entity_system().entity(m_self_id)->position()->x() - entity_system().entity(m_self_id)->position()->w()/2.0;
	double distance_y = entity_system().entity(m_target_id)->position()->y() + entity_system().entity(m_target_id)->position()->h()/2.0 - entity_system().entity(m_self_id)->position()->y() - entity_system().entity(m_self_id)->position()->h()/2.0;

	m_walk_dir = sign(distance_x) * (abs(distance_x) > m_attack_range);
	m_look_dir = distance_x > 0 ? RIGHT : distance_x < 0 ? LEFT : m_look_dir;

	m_jump = distance_y > 100 && distance_y < 200 && abs(distance_x) < 200;
}




