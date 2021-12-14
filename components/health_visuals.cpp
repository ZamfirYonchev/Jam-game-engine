/*
 * health_visuals.cpp
 *
 *  Created on: Dec 4, 2021
 *      Author: zamfi
 */

#include "health_visuals.h"
#include "health.h"

AnimationFrame HealthVisuals::animation_frame(const int rx, const int) const
{
	const Health& health = m_health_accessor(m_self_id);
	const bool active_animation = (m_repeat_x != 0) && (health.max_hp() != 0) && (health.max_hp()*rx < health.hp()*m_repeat_x);
	return {active_animation ? m_active_anim_id : m_inactive_anim_id
		  , active_animation ? m_active_animation_time/m_active_animation_frame_delay
							 : m_inactive_animation_time/m_inactive_animation_frame_delay};
}

