/*
 * character_health_visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_HEALTH_VISUALS_H_
#define COMPONENTS_HEALTH_VISUALS_H_

#include "visuals.h"
#include "health.h"
#include "../systems/resource_system.h"

template<typename EntitySystemT>
class HealthVisuals : public Visuals
{
public:
	using Base = Visuals;
	HealthVisuals
	   ( const AnimationID active_id
	   , const AnimationID inactive_id
	   , const int repeat_x
	   , const ResourceSystem& resource_system
	   , const EntityID self_id
	   , const EntitySystemT& entity_system
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
	, m_entity_system(entity_system)
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

    AnimationFrame animation_frame(const int rx, const int ry) const
    {
    	const auto& health = m_entity_system.template entity_component<Health>(m_self_id);
    	const bool active_animation = (m_repeat_x != 0) && (health.max_hp() != 0) && (health.max_hp()*rx < health.hp()*m_repeat_x);
    	return {active_animation ? m_active_anim_id : m_inactive_anim_id
    		  , active_animation ? m_active_animation_time/m_active_animation_frame_delay
    				  	  	  	 : m_inactive_animation_time/m_inactive_animation_frame_delay};
    }

    int repeat_x() const { return m_repeat_x; }
    int repeat_y() const { return 1; }
    void set_repeat_x(const int val) { m_repeat_x = val; }
    void set_repeat_y(const int val) {}
    VisualLayer layer() const { return VisualLayer::CLOSE_BACKGROUND; }
    void set_layer(VisualLayer val) {}

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
    const EntitySystemT& m_entity_system;
};

#endif /* COMPONENTS_HEALTH_VISUALS_H_ */
