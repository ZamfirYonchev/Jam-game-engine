/*
 * menu_item_visuals.h
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_MENU_ITEM_VISUALS_H_
#define COMPONENTS_MENU_ITEM_VISUALS_H_

#include "visuals_enums.h"
#include "../systems/resource_system.h"
#include "../types.h"
#include "../command_value.h"

class Control;

class MenuItemVisuals
{
public:
	MenuItemVisuals
	( const AnimationID inactive_anim_id
	, const AnimationID focus_anim_id
	, const AnimationID select_anim_id
	, const ResourceSystem& resource_system
	, const EntityID self_id
	, std::function<const Control&(const EntityID id)> control_accessor
	)
	: m_self_id{self_id}
	, m_inactive_anim_id{inactive_anim_id}
	, m_focus_anim_id{focus_anim_id}
	, m_select_anim_id{select_anim_id}
    , m_inactive_animation_frame_delay{1}
    , m_focus_animation_frame_delay{1}
    , m_select_animation_frame_delay{1}
    , m_inactive_animation_time_max{1}
    , m_focus_animation_time_max{1}
    , m_select_animation_time_max{1}
    , m_inactive_anim_time{0}
    , m_focus_anim_time{0}
    , m_select_anim_time{0}
	, m_control_accessor{std::move(control_accessor)}
	{
		const auto& inactive_anim_opt = resource_system.animation(m_inactive_anim_id);

		if(inactive_anim_opt)
		{
			m_inactive_animation_frame_delay = inactive_anim_opt->get().frame_delay_ms();
			m_inactive_animation_time_max = m_inactive_animation_frame_delay*inactive_anim_opt->get().frame_count();
		}
		else
		{ /*error idle_anim_id*/ }

		const auto& focus_anim_opt = resource_system.animation(m_focus_anim_id);

		if(focus_anim_opt)
		{
			m_focus_animation_frame_delay = focus_anim_opt->get().frame_delay_ms();
			m_focus_animation_time_max = m_focus_animation_frame_delay*focus_anim_opt->get().frame_count();
		}
		else
		{ /*error idle_anim_id*/ }

		const auto& select_anim_opt = resource_system.animation(m_select_anim_id);

		if(select_anim_opt)
		{
			m_select_animation_frame_delay = select_anim_opt->get().frame_delay_ms();
			m_select_animation_time_max = m_select_animation_frame_delay*select_anim_opt->get().frame_count();
		}
		else
		{ /*error idle_anim_id*/ }
	}

    template<typename ExtractorF>
	MenuItemVisuals
	( ExtractorF&& extract
	, const ResourceSystem& resource_system
	, const CommandValue& self_id
	, const std::function<const Control&(const EntityID id)>& control_accessor
	)
	: MenuItemVisuals
	  { extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , resource_system
	  , EntityID(self_id.integer())
	  , control_accessor
	  }
	{}

    void print(std::ostream& to) const
    {
    	to << "UseMenuItemVisuals "
    	   << m_inactive_anim_id << " "
    	   << m_focus_anim_id << " "
    	   << m_select_anim_id << " ";
    }

    void update_animation(const Time time_diff)
    {
    	m_inactive_anim_time = (m_inactive_anim_time+int(time_diff))%m_inactive_animation_time_max;
    	m_focus_anim_time = (m_focus_anim_time+int(time_diff))%m_focus_animation_time_max;
    	m_select_anim_time = (m_select_anim_time+int(time_diff))%m_select_animation_time_max;
    }

    AnimationFrame animation_frame(const int rx, const int ry) const;
    int repeat_x() const { return 1; }
    int repeat_y() const { return 1; }
    void set_repeat_x(const int val) {}
    void set_repeat_y(const int val) {}
    VisualLayer layer() const { return VisualLayer::FOREGROUND; }
    void set_layer(VisualLayer val) {}

private:
    EntityID m_self_id;
    AnimationID m_inactive_anim_id;
    AnimationID m_focus_anim_id;
    AnimationID m_select_anim_id;
    int m_inactive_animation_frame_delay;
    int m_focus_animation_frame_delay;
    int m_select_animation_frame_delay;
    int m_inactive_animation_time_max;
    int m_focus_animation_time_max;
    int m_select_animation_time_max;
    int m_inactive_anim_time;
    int m_focus_anim_time;
    int m_select_anim_time;
    std::function<const Control&(const EntityID id)> m_control_accessor;
};

#endif /* COMPONENTS_MENU_ITEM_VISUALS_H_ */
