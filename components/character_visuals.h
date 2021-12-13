/*
 * character_visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_CHARACTER_VISUALS_H_
#define COMPONENTS_CHARACTER_VISUALS_H_

#include "visuals_enums.h"
#include "../systems/resource_system.h"
#include "../types.h"
#include "../command_value.h"

class Control;
class Movement;
class Collision;
class Health;

class CharacterVisuals
{
public:
    enum class RenderStates { IDLE, WALK, JUMP, FALL, ATTACK, HIT, DEAD};

    CharacterVisuals
	( const AnimationID idle_anim_id
	, const AnimationID walk_anim_id
	, const AnimationID jump_anim_id
	, const AnimationID fall_anim_id
	, const AnimationID attack_anim_id
	, const AnimationID hit_anim_id
	, const AnimationID dead_anim_id
	, const ResourceSystem& resource_system
	, const EntityID self_id
	, const ComponentAccess<const Control>& control_accessor
	, const ComponentAccess<const Movement>& movement_accessor
	, const ComponentAccess<const Collision>& collision_accessor
	, const ComponentAccess<const Health>& health_accessor
	)
	: m_current_state(RenderStates::IDLE)
	, m_current_anim_id{idle_anim_id}
	, m_idle_anim_id{idle_anim_id}
	, m_walk_anim_id{walk_anim_id}
	, m_jump_anim_id{jump_anim_id}
	, m_fall_anim_id{fall_anim_id}
	, m_attack_anim_id{attack_anim_id}
	, m_hit_anim_id{hit_anim_id}
	, m_dead_anim_id{dead_anim_id}
	, m_current_anim_frame_delay{1}
	, m_idle_anim_frame_delay{1}
	, m_walk_anim_frame_delay{1}
	, m_jump_anim_frame_delay{1}
	, m_fall_anim_frame_delay{1}
	, m_attack_anim_frame_delay{1}
	, m_hit_anim_frame_delay{1}
	, m_dead_anim_frame_delay{1}
	, m_current_anim_time_max{1}
	, m_idle_anim_time_max{1}
	, m_walk_anim_time_max{1}
	, m_jump_anim_time_max{1}
	, m_fall_anim_time_max{1}
	, m_attack_anim_time_max{1}
	, m_hit_anim_time_max{1}
	, m_dead_anim_time_max{1}
	, m_anim_time{0}
	, m_last_frame{false}
	, m_layer{VisualLayer::ACTION}
	, m_self_id{self_id}
	, m_control_accessor{control_accessor}
	, m_movement_accessor{movement_accessor}
	, m_collision_accessor{collision_accessor}
	, m_health_accessor{health_accessor}
	{
		const auto& idle_anim_opt = resource_system.animation(idle_anim_id);

		if(idle_anim_opt)
		{
			m_idle_anim_frame_delay = idle_anim_opt->get().frame_delay_ms();
			m_idle_anim_time_max = m_idle_anim_frame_delay*idle_anim_opt->get().frame_count();
		}
		else
		{ /*error idle_anim_id*/ }

		const auto& walk_anim_opt = resource_system.animation(walk_anim_id);

		if(walk_anim_opt)
		{
			m_walk_anim_frame_delay = walk_anim_opt->get().frame_delay_ms();
			m_walk_anim_time_max = m_walk_anim_frame_delay*walk_anim_opt->get().frame_count();
		}
		else
		{ /*error walk_anim_id*/ }

		const auto& jump_anim_opt = resource_system.animation(jump_anim_id);

		if(jump_anim_opt)
		{
			m_jump_anim_frame_delay = jump_anim_opt->get().frame_delay_ms();
			m_jump_anim_time_max = m_jump_anim_frame_delay*jump_anim_opt->get().frame_count();
		}
		else
		{ /*error jump_anim_id*/ }

		const auto& fall_anim_opt = resource_system.animation(fall_anim_id);

		if(fall_anim_opt)
		{
			m_fall_anim_frame_delay = fall_anim_opt->get().frame_delay_ms();
			m_fall_anim_time_max = m_fall_anim_frame_delay*fall_anim_opt->get().frame_count();
		}
		else
		{ /*error fall_anim_id*/ }

		const auto& attack_anim_opt = resource_system.animation(attack_anim_id);

		if(attack_anim_opt)
		{
			m_attack_anim_frame_delay = attack_anim_opt->get().frame_delay_ms();
			m_attack_anim_time_max = m_attack_anim_frame_delay*attack_anim_opt->get().frame_count();
		}
		else
		{ /*error attack_anim_id*/ }

		const auto& hit_anim_opt = resource_system.animation(hit_anim_id);

		if(hit_anim_opt)
		{
			m_hit_anim_frame_delay = hit_anim_opt->get().frame_delay_ms();
			m_hit_anim_time_max = m_hit_anim_frame_delay*hit_anim_opt->get().frame_count();
		}
		else
		{ /*error hit_anim_id*/ }

		const auto& dead_anim_opt = resource_system.animation(dead_anim_id);

		if(dead_anim_opt)
		{
			m_dead_anim_frame_delay = dead_anim_opt->get().frame_delay_ms();
			m_dead_anim_time_max = m_dead_anim_frame_delay*dead_anim_opt->get().frame_count();
		}
		else
		{ /*error dead_anim_id*/ }

		set_new_state(RenderStates::IDLE);
	}

    template<typename ExtractorF>
	CharacterVisuals
	( ExtractorF&& extract
	, const ResourceSystem& resource_system
	, const CommandValue& self_id
	, const ComponentAccess<const Control>& control_accessor
	, const ComponentAccess<const Movement>& movement_accessor
	, const ComponentAccess<const Collision>& collision_accessor
	, const ComponentAccess<const Health>& health_accessor
	)
	: CharacterVisuals
	  { extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , resource_system
	  , EntityID(self_id.integer())
	  , control_accessor
	  , movement_accessor
	  , collision_accessor
	  , health_accessor
	  }
	{}

    void print(std::ostream& to) const
    {
    	to << "UseCharacterVisuals "
    	   << m_idle_anim_id << " "
		   << m_walk_anim_id << " "
		   << m_jump_anim_id << " "
		   << m_fall_anim_id << " "
		   << m_attack_anim_id << " "
		   << m_hit_anim_id << " "
		   << m_dead_anim_id << " ";
    }

    void update_animation(const Time time_diff);
    AnimationFrame animation_frame(const int rx, const int ry) const
    {
    	return {m_current_anim_id, m_anim_time/m_current_anim_frame_delay};
    }

    int repeat_x() const { return 1; }
    int repeat_y() const { return 1; }
    void set_repeat_x(const int val) {}
    void set_repeat_y(const int val) {}
    VisualLayer layer() const { return m_layer; }
    void set_layer(const VisualLayer val) { m_layer = val; }

private:
	RenderStates m_current_state;
    AnimationID m_current_anim_id;
    AnimationID m_idle_anim_id;
	AnimationID m_walk_anim_id;
	AnimationID m_jump_anim_id;
	AnimationID m_fall_anim_id;
	AnimationID m_attack_anim_id;
	AnimationID m_hit_anim_id;
	AnimationID m_dead_anim_id;
    int m_current_anim_frame_delay;
    int m_idle_anim_frame_delay;
    int m_walk_anim_frame_delay;
    int m_jump_anim_frame_delay;
    int m_fall_anim_frame_delay;
    int m_attack_anim_frame_delay;
    int m_hit_anim_frame_delay;
    int m_dead_anim_frame_delay;
    int m_current_anim_time_max;
    int m_idle_anim_time_max;
    int m_walk_anim_time_max;
    int m_jump_anim_time_max;
    int m_fall_anim_time_max;
    int m_attack_anim_time_max;
    int m_hit_anim_time_max;
    int m_dead_anim_time_max;
    int m_anim_time;
    bool m_last_frame;
    VisualLayer m_layer;
    EntityID m_self_id;
    ComponentAccess<const Control> m_control_accessor;
    ComponentAccess<const Movement> m_movement_accessor;
    ComponentAccess<const Collision> m_collision_accessor;
    ComponentAccess<const Health> m_health_accessor;

    void set_new_state(RenderStates new_state)
    {
		switch(new_state)
    	{
    		default:
    		case RenderStates::IDLE:
    		{
    			m_current_anim_id = m_idle_anim_id;
    			m_current_anim_frame_delay = m_idle_anim_frame_delay;
    			m_current_anim_time_max = m_idle_anim_time_max;
    		}
    		break;

    		case RenderStates::WALK:
    		{
    			m_current_anim_id = m_walk_anim_id;
    			m_current_anim_frame_delay = m_walk_anim_frame_delay;
    			m_current_anim_time_max = m_walk_anim_time_max;
    		}
    		break;

    		case RenderStates::JUMP:
    		{
    			m_current_anim_id = m_jump_anim_id;
    			m_current_anim_frame_delay = m_jump_anim_frame_delay;
    			m_current_anim_time_max = m_jump_anim_time_max;
    		}
    		break;

    		case RenderStates::FALL:
    		{
    			m_current_anim_id = m_fall_anim_id;
    			m_current_anim_frame_delay = m_fall_anim_frame_delay;
    			m_current_anim_time_max = m_fall_anim_time_max;
    		}
    		break;

    		case RenderStates::ATTACK:
    		{
    			m_current_anim_id = m_attack_anim_id;
    			m_current_anim_frame_delay = m_attack_anim_frame_delay;
    			m_current_anim_time_max = m_attack_anim_time_max;
    		}
    		break;

    		case RenderStates::HIT:
    		{
    			m_current_anim_id = m_hit_anim_id;
    			m_current_anim_frame_delay = m_hit_anim_frame_delay;
    			m_current_anim_time_max = m_hit_anim_time_max;
    		}
    		break;

    		case RenderStates::DEAD:
    		{
    			m_current_anim_id = m_dead_anim_id;
    			m_current_anim_frame_delay = m_dead_anim_frame_delay;
    			m_current_anim_time_max = m_dead_anim_time_max;
    		}
    		break;

    	}

		m_current_state = new_state;
        m_anim_time = 0;
        m_last_frame = false;
    }

    void advance_animation(const int time_diff)
    {
    	m_anim_time = (m_anim_time+time_diff)%m_current_anim_time_max;
    	m_last_frame = ((m_anim_time+time_diff)/m_current_anim_frame_delay) == (m_current_anim_time_max/m_current_anim_frame_delay);
    }
};

#endif /* COMPONENTS_CHARACTER_VISUALS_H_ */
