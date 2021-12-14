/*
 * character_health_visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_HEALTH_VISUALS_H_
#define COMPONENTS_HEALTH_VISUALS_H_

#include "visuals_enums.h"
#include "../systems/resource_system.h"
#include "../types.h"
#include "../command_value.h"

class Health;

class HealthVisuals
{
public:
	HealthVisuals
	( const AnimationID active_id
	, const AnimationID inactive_id
	, const int repeat_x
	, const ResourceSystem& resource_system
	, const EntityID self_id
	, const ComponentAccess<const Health>& health_accessor
	)
	: m_active_anim_id{active_id}
	, m_inactive_anim_id{inactive_id}
	, m_active_animation_frame_delay{1}
	, m_inactive_animation_frame_delay{1}
	, m_active_animation_time_max{1}
	, m_inactive_animation_time_max{1}
	, m_active_animation_time{0}
	, m_inactive_animation_time{0}
	, m_repeat_x{repeat_x}
	, m_self_id{self_id}
	, m_health_accessor(health_accessor)
	{
		const auto& active_anim_opt = resource_system.animation(active_id);

		if(active_anim_opt)
		{
			m_active_animation_frame_delay = active_anim_opt->get().frame_delay_ms();
			m_active_animation_time_max = m_active_animation_frame_delay*active_anim_opt->get().frame_count();
		}
		else
		{ /*error active_id*/ }

		const auto& inactive_anim_opt = resource_system.animation(inactive_id);

		if(inactive_anim_opt)
		{
			m_inactive_animation_frame_delay = inactive_anim_opt->get().frame_delay_ms();
			m_inactive_animation_time_max = m_inactive_animation_frame_delay*inactive_anim_opt->get().frame_count();
		}
		else
		{ /*error inactive_id*/ }
	}

    template<typename ExtractorF>
	HealthVisuals
	( ExtractorF&& extract
	, const ResourceSystem& resource_system
	, const CommandValue& self_id
	, const ComponentAccess<const Health>& health_accessor
	)
	: HealthVisuals
	  { extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , resource_system
	  , EntityID(self_id.integer())
	  , health_accessor
	  }
	{}

    void print(std::ostream& to) const
    {
    	to << "UseHealthVisuals "
    	   << m_active_anim_id << " "
    	   << m_inactive_anim_id << " "
		   << m_repeat_x << " ";
    }

    void update_animation(const Time time_diff)
    {
    	m_active_animation_time = (m_active_animation_time + int(time_diff)) % m_active_animation_time_max;
    	m_inactive_animation_time = (m_inactive_animation_time + int(time_diff)) % m_inactive_animation_time_max;
    }

    AnimationFrame animation_frame(const int rx, const int ry) const;
    int repeat_x() const { return m_repeat_x; }
    int repeat_y() const { return 1; }
    void set_repeat_x(const int val) { m_repeat_x = val; }
    void set_repeat_y(const int) {}
    VisualLayer layer() const { return VisualLayer::CLOSE_BACKGROUND; }
    void set_layer(VisualLayer) {}

private:
    AnimationID m_active_anim_id, m_inactive_anim_id;
    int m_active_animation_frame_delay;
    int m_inactive_animation_frame_delay;
    int m_active_animation_time_max;
    int m_inactive_animation_time_max;
    int m_active_animation_time;
    int m_inactive_animation_time;
    int m_repeat_x;
    EntityID m_self_id;
    ComponentAccess<const Health> m_health_accessor;
};

#endif /* COMPONENTS_HEALTH_VISUALS_H_ */
