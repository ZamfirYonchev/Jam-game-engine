/*
 * menu_item_visuals.cpp
 *
 *  Created on: Dec 4, 2021
 *      Author: zamfi
 */

#include "menu_item_visuals.h"
#include "control.h"

AnimationFrame MenuItemVisuals::animation_frame(const int, const int) const
{
	const Control& control = m_control_accessor(m_self_id);
	return {control.decision_attack() ? m_select_anim_id
		 : (control.decision_vertical() != 0) ? m_focus_anim_id
		 : m_inactive_anim_id
		 ,
		   control.decision_attack() ? m_select_anim_time/m_select_animation_frame_delay
		 : (control.decision_vertical() != 0) ? m_focus_anim_time/m_focus_animation_frame_delay
		 : m_inactive_anim_time/m_inactive_animation_frame_delay,
		   };
}
