/*
 * character_topdown_visuals.h
 *
 *  Created on: Jan 27, 2022
 *      Author: zamfi
 */

#ifndef COMPONENTS_CHARACTER_TOPDOWN_VISUALS_H_
#define COMPONENTS_CHARACTER_TOPDOWN_VISUALS_H_

#include "visuals_enums.h"
#include "../types.h"
#include "collision_enums.h"

template<typename ControlT, typename HealthT>
class CharacterTopDownVisuals
{
public:
    enum class RenderStates
	{ IDLE_DOWN
    , IDLE_UP
	, IDLE_SIDE
	, WALK_DOWN
	, WALK_UP
	, WALK_SIDE
	, USE_DOWN
	, USE_UP
	, USE_SIDE
	, DEAD
	};

    template<typename AnimationAccessorT>
    CharacterTopDownVisuals
	( const AnimationID idle_down_anim_id
	, const AnimationID idle_up_anim_id
	, const AnimationID idle_side_anim_id
	, const AnimationID walk_down_anim_id
	, const AnimationID walk_up_anim_id
	, const AnimationID walk_side_anim_id
	, const AnimationID use_down_anim_id
	, const AnimationID use_up_anim_id
	, const AnimationID use_side_anim_id
	, const AnimationID dead_anim_id
	, const AnimationAccessorT& animation_access
	, const EntityID self_id
	, ComponentAccess<const ControlT> control_accessor
	, ComponentAccess<const HealthT> health_accessor
	)
	: m_current_state{RenderStates::IDLE_DOWN}
	, m_current_anim_id{idle_down_anim_id}
	, m_idle_down_anim_id{idle_down_anim_id}
	, m_idle_up_anim_id{idle_up_anim_id}
	, m_idle_side_anim_id{idle_side_anim_id}
	, m_walk_down_anim_id{walk_down_anim_id}
	, m_walk_up_anim_id{walk_up_anim_id}
	, m_walk_side_anim_id{walk_side_anim_id}
	, m_use_down_anim_id{use_down_anim_id}
	, m_use_up_anim_id{use_up_anim_id}
	, m_use_side_anim_id{use_side_anim_id}
	, m_dead_anim_id{dead_anim_id}
	, m_current_anim_frame_delay{1}
	, m_idle_down_anim_frame_delay{1}
	, m_idle_up_anim_frame_delay{1}
	, m_idle_side_anim_frame_delay{1}
	, m_walk_down_anim_frame_delay{1}
	, m_walk_up_anim_frame_delay{1}
	, m_walk_side_anim_frame_delay{1}
	, m_use_down_anim_frame_delay{1}
	, m_use_up_anim_frame_delay{1}
	, m_use_side_anim_frame_delay{1}
	, m_dead_anim_frame_delay{1}
	, m_current_anim_time_max{1}
	, m_idle_down_anim_time_max{1}
	, m_idle_up_anim_time_max{1}
	, m_idle_side_anim_time_max{1}
	, m_walk_down_anim_time_max{1}
	, m_walk_up_anim_time_max{1}
	, m_walk_side_anim_time_max{1}
	, m_use_down_anim_time_max{1}
	, m_use_up_anim_time_max{1}
	, m_use_side_anim_time_max{1}
	, m_dead_anim_time_max{1}
	, m_anim_time{0}
	, m_last_frame{false}
	, m_look_dir_x{0.0}
	, m_look_dir_y{-1.0}
	, m_layer{VisualLayer::ACTION}
	, m_self_id{self_id}
	, m_control_accessor{std::move(control_accessor)}
	, m_health_accessor{std::move(health_accessor)}
	{
		const auto& idle_down_anim_opt = animation_access(idle_down_anim_id);

		if(idle_down_anim_opt)
		{
			m_idle_down_anim_frame_delay = idle_down_anim_opt->get().frame_delay_ms();
			m_idle_down_anim_time_max = m_idle_down_anim_frame_delay*idle_down_anim_opt->get().frame_count();
		}
		else
		{ /*error idle_anim_id*/ }

		const auto& idle_up_anim_opt = animation_access(idle_up_anim_id);

		if(idle_up_anim_opt)
		{
			m_idle_up_anim_frame_delay = idle_up_anim_opt->get().frame_delay_ms();
			m_idle_up_anim_time_max = m_idle_up_anim_frame_delay*idle_up_anim_opt->get().frame_count();
		}
		else
		{ /*error idle_anim_id*/ }

		const auto& idle_side_anim_opt = animation_access(idle_side_anim_id);

		if(idle_side_anim_opt)
		{
			m_idle_side_anim_frame_delay = idle_side_anim_opt->get().frame_delay_ms();
			m_idle_side_anim_time_max = m_idle_side_anim_frame_delay*idle_side_anim_opt->get().frame_count();
		}
		else
		{ /*error idle_anim_id*/ }

		const auto& walk_down_anim_opt = animation_access(walk_down_anim_id);

		if(walk_down_anim_opt)
		{
			m_walk_down_anim_frame_delay = walk_down_anim_opt->get().frame_delay_ms();
			m_walk_down_anim_time_max = m_walk_down_anim_frame_delay*walk_down_anim_opt->get().frame_count();
		}
		else
		{ /*error walk_anim_id*/ }

		const auto& walk_up_anim_opt = animation_access(walk_up_anim_id);

		if(walk_up_anim_opt)
		{
			m_walk_up_anim_frame_delay = walk_up_anim_opt->get().frame_delay_ms();
			m_walk_up_anim_time_max = m_walk_up_anim_frame_delay*walk_up_anim_opt->get().frame_count();
		}
		else
		{ /*error walk_anim_id*/ }

		const auto& walk_side_anim_opt = animation_access(walk_side_anim_id);

		if(walk_side_anim_opt)
		{
			m_walk_side_anim_frame_delay = walk_side_anim_opt->get().frame_delay_ms();
			m_walk_side_anim_time_max = m_walk_side_anim_frame_delay*walk_side_anim_opt->get().frame_count();
		}
		else
		{ /*error walk_anim_id*/ }

		const auto& use_down_anim_opt = animation_access(use_down_anim_id);

		if(use_down_anim_opt)
		{
			m_use_down_anim_frame_delay = use_down_anim_opt->get().frame_delay_ms();
			m_use_down_anim_time_max = m_use_down_anim_frame_delay*use_down_anim_opt->get().frame_count();
		}
		else
		{ /*error jump_anim_id*/ }

		const auto& use_up_anim_opt = animation_access(use_up_anim_id);

		if(use_up_anim_opt)
		{
			m_use_up_anim_frame_delay = use_up_anim_opt->get().frame_delay_ms();
			m_use_up_anim_time_max = m_use_up_anim_frame_delay*use_up_anim_opt->get().frame_count();
		}
		else
		{ /*error jump_anim_id*/ }

		const auto& use_side_anim_opt = animation_access(use_side_anim_id);

		if(use_side_anim_opt)
		{
			m_use_side_anim_frame_delay = use_side_anim_opt->get().frame_delay_ms();
			m_use_side_anim_time_max = m_use_side_anim_frame_delay*use_side_anim_opt->get().frame_count();
		}
		else
		{ /*error jump_anim_id*/ }

		const auto& dead_anim_opt = animation_access(dead_anim_id);

		if(dead_anim_opt)
		{
			m_dead_anim_frame_delay = dead_anim_opt->get().frame_delay_ms();
			m_dead_anim_time_max = m_dead_anim_frame_delay*dead_anim_opt->get().frame_count();
		}
		else
		{ /*error dead_anim_id*/ }

		set_new_state(RenderStates::IDLE_DOWN);
	}

    template<typename ExtractorF, typename AnimationAccessorT, typename SelfIDObtainerF>
	CharacterTopDownVisuals
	( ExtractorF&& extract
	, const AnimationAccessorT& animation_access
	, const SelfIDObtainerF& obtain_self_id
	, ComponentAccess<const ControlT> control_accessor
	, ComponentAccess<const HealthT> health_accessor
	)
	: CharacterTopDownVisuals
	  { extract()
	  , extract()
	  , extract()
	  , extract()
	  , extract()
	  , extract()
	  , extract()
	  , extract()
	  , extract()
	  , extract()
	  , animation_access
	  , obtain_self_id()
	  , std::move(control_accessor)
	  , std::move(health_accessor)
	  }
	{}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseCharacterTopdownVisuals");
    	insert(m_idle_down_anim_id);
    	insert(m_idle_up_anim_id);
    	insert(m_idle_side_anim_id);
    	insert(m_walk_down_anim_id);
    	insert(m_walk_up_anim_id);
    	insert(m_walk_side_anim_id);
    	insert(m_use_down_anim_id);
    	insert(m_use_up_anim_id);
    	insert(m_use_side_anim_id);
    	insert(m_dead_anim_id);
    }

    void update_animation(const Time time_diff)
    {
    	const auto& control = m_control_accessor(m_self_id);
    	const auto& health = m_health_accessor(m_self_id);

    	if(control.decision_vertical() != 0 || control.decision_walk() != 0)
    	{
    		m_look_dir_x = control.decision_walk();
    		m_look_dir_y = control.decision_vertical();
    	}

    	switch(m_current_state)
    	{
    		default:
    		case RenderStates::IDLE_DOWN:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(control.decision_attack()) set_new_state(RenderStates::USE_DOWN);
    			else if(control.decision_vertical() < 0) set_new_state(RenderStates::WALK_DOWN);
    			else if(control.decision_vertical() > 0) set_new_state(RenderStates::WALK_UP);
    			else if(control.decision_walk() != 0) set_new_state(RenderStates::WALK_SIDE);
    			else advance_animation(time_diff);
    		break;

    		case RenderStates::IDLE_UP:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(control.decision_attack()) set_new_state(RenderStates::USE_UP);
    			else if(control.decision_vertical() > 0) set_new_state(RenderStates::WALK_UP);
    			else if(control.decision_vertical() < 0) set_new_state(RenderStates::WALK_DOWN);
    			else if(control.decision_walk() != 0) set_new_state(RenderStates::WALK_SIDE);
    			else advance_animation(time_diff);
    		break;

    		case RenderStates::IDLE_SIDE:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(control.decision_attack()) set_new_state(RenderStates::USE_SIDE);
    			else if(control.decision_walk() != 0) set_new_state(RenderStates::WALK_SIDE);
    			else if(control.decision_vertical() > 0) set_new_state(RenderStates::WALK_UP);
    			else if(control.decision_vertical() < 0) set_new_state(RenderStates::WALK_DOWN);
    			else advance_animation(time_diff);
    		break;

    		case RenderStates::WALK_DOWN:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(control.decision_attack()) set_new_state(RenderStates::USE_DOWN);
    			else if(control.decision_vertical() < 0) advance_animation(time_diff);
    			else if(control.decision_vertical() > 0) set_new_state(RenderStates::WALK_UP);
    			else if(control.decision_walk() != 0) set_new_state(RenderStates::WALK_SIDE);
    			else set_new_state(RenderStates::IDLE_DOWN);
    		break;

    		case RenderStates::WALK_UP:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(control.decision_attack()) set_new_state(RenderStates::USE_UP);
    			else if(control.decision_vertical() > 0) advance_animation(time_diff);
    			else if(control.decision_vertical() < 0) set_new_state(RenderStates::WALK_DOWN);
    			else if(control.decision_walk() != 0) set_new_state(RenderStates::WALK_SIDE);
    			else set_new_state(RenderStates::IDLE_UP);
    		break;

    		case RenderStates::WALK_SIDE:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(control.decision_attack()) set_new_state(RenderStates::USE_SIDE);
    			else if(control.decision_walk() != 0) advance_animation(time_diff);
    			else if(control.decision_vertical() > 0) set_new_state(RenderStates::WALK_UP);
    			else if(control.decision_vertical() < 0) set_new_state(RenderStates::WALK_DOWN);
    			else set_new_state(RenderStates::IDLE_SIDE);
    		break;

    		case RenderStates::USE_DOWN:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(m_last_frame && (control.decision_vertical() < 0)) set_new_state(RenderStates::WALK_DOWN);
    			else if(m_last_frame && (control.decision_vertical() > 0)) set_new_state(RenderStates::WALK_UP);
    			else if(m_last_frame && (control.decision_walk() != 0)) set_new_state(RenderStates::WALK_SIDE);
    			else if(m_last_frame) set_new_state(RenderStates::IDLE_DOWN);
    			else advance_animation(time_diff);
    		break;

    		case RenderStates::USE_UP:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(m_last_frame && (control.decision_vertical() > 0)) set_new_state(RenderStates::WALK_UP);
    			else if(m_last_frame && (control.decision_vertical() < 0)) set_new_state(RenderStates::WALK_DOWN);
    			else if(m_last_frame && (control.decision_walk() != 0)) set_new_state(RenderStates::WALK_SIDE);
    			else if(m_last_frame) set_new_state(RenderStates::IDLE_UP);
    			else advance_animation(time_diff);
    		break;

    		case RenderStates::USE_SIDE:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(m_last_frame && (control.decision_walk() != 0)) set_new_state(RenderStates::WALK_SIDE);
    			else if(m_last_frame && (control.decision_vertical() < 0)) set_new_state(RenderStates::WALK_DOWN);
    			else if(m_last_frame && (control.decision_vertical() > 0)) set_new_state(RenderStates::WALK_UP);
    			else if(m_last_frame) set_new_state(RenderStates::IDLE_SIDE);
    			else advance_animation(time_diff);
    		break;

    		case RenderStates::DEAD:
    			if(m_last_frame == false)
    				advance_animation(time_diff);
    			//else do nothing
    		break;
    	}
    }

    AnimationFrame animation_frame(const int, const int) const
    {
    	return {m_current_anim_id, m_anim_time/m_current_anim_frame_delay};
    }

    int repeat_x() const { return 1; }
    int repeat_y() const { return 1; }
    double look_dir_x() const { return m_look_dir_x; }
    double look_dir_y() const { return m_look_dir_y; }

    void set_repeat_x(const int) {}
    void set_repeat_y(const int) {}
    VisualLayer layer() const { return m_layer; }
    void set_layer(const VisualLayer val) { m_layer = val; }

private:
	RenderStates m_current_state;
    AnimationID m_current_anim_id;
    AnimationID m_idle_down_anim_id;
    AnimationID m_idle_up_anim_id;
    AnimationID m_idle_side_anim_id;
	AnimationID m_walk_down_anim_id;
	AnimationID m_walk_up_anim_id;
	AnimationID m_walk_side_anim_id;
	AnimationID m_use_down_anim_id;
	AnimationID m_use_up_anim_id;
	AnimationID m_use_side_anim_id;
	AnimationID m_dead_anim_id;
    int m_current_anim_frame_delay;
    int m_idle_down_anim_frame_delay;
    int m_idle_up_anim_frame_delay;
    int m_idle_side_anim_frame_delay;
    int m_walk_down_anim_frame_delay;
    int m_walk_up_anim_frame_delay;
    int m_walk_side_anim_frame_delay;
    int m_use_down_anim_frame_delay;
    int m_use_up_anim_frame_delay;
    int m_use_side_anim_frame_delay;
    int m_dead_anim_frame_delay;
    int m_current_anim_time_max;
    int m_idle_down_anim_time_max;
    int m_idle_up_anim_time_max;
    int m_idle_side_anim_time_max;
    int m_walk_down_anim_time_max;
    int m_walk_up_anim_time_max;
    int m_walk_side_anim_time_max;
    int m_use_down_anim_time_max;
    int m_use_up_anim_time_max;
    int m_use_side_anim_time_max;
    int m_dead_anim_time_max;
    int m_anim_time;
    bool m_last_frame;
    double m_look_dir_x;
    double m_look_dir_y;
    VisualLayer m_layer;
    EntityID m_self_id;
    ComponentAccess<const ControlT> m_control_accessor;
    ComponentAccess<const HealthT> m_health_accessor;

    void set_new_state(RenderStates new_state)
    {
		switch(new_state)
    	{
    		default:
    		case RenderStates::IDLE_DOWN:
    		{
    			m_current_anim_id = m_idle_down_anim_id;
    			m_current_anim_frame_delay = m_idle_down_anim_frame_delay;
    			m_current_anim_time_max = m_idle_down_anim_time_max;
    		}
    		break;

    		case RenderStates::IDLE_UP:
    		{
    			m_current_anim_id = m_idle_up_anim_id;
    			m_current_anim_frame_delay = m_idle_up_anim_frame_delay;
    			m_current_anim_time_max = m_idle_up_anim_time_max;
    		}
    		break;

    		case RenderStates::IDLE_SIDE:
    		{
    			m_current_anim_id = m_idle_side_anim_id;
    			m_current_anim_frame_delay = m_idle_side_anim_frame_delay;
    			m_current_anim_time_max = m_idle_side_anim_time_max;
    		}
    		break;

    		case RenderStates::WALK_DOWN:
    		{
    			m_current_anim_id = m_walk_down_anim_id;
    			m_current_anim_frame_delay = m_walk_down_anim_frame_delay;
    			m_current_anim_time_max = m_walk_down_anim_time_max;
    		}
    		break;

    		case RenderStates::WALK_UP:
    		{
    			m_current_anim_id = m_walk_up_anim_id;
    			m_current_anim_frame_delay = m_walk_up_anim_frame_delay;
    			m_current_anim_time_max = m_walk_up_anim_time_max;
    		}
    		break;

    		case RenderStates::WALK_SIDE:
    		{
    			m_current_anim_id = m_walk_side_anim_id;
    			m_current_anim_frame_delay = m_walk_side_anim_frame_delay;
    			m_current_anim_time_max = m_walk_side_anim_time_max;
    		}
    		break;

    		case RenderStates::USE_DOWN:
    		{
    			m_current_anim_id = m_use_down_anim_id;
    			m_current_anim_frame_delay = m_use_down_anim_frame_delay;
    			m_current_anim_time_max = m_use_down_anim_time_max;
    		}
    		break;

    		case RenderStates::USE_UP:
    		{
    			m_current_anim_id = m_use_up_anim_id;
    			m_current_anim_frame_delay = m_use_up_anim_frame_delay;
    			m_current_anim_time_max = m_use_up_anim_time_max;
    		}
    		break;

    		case RenderStates::USE_SIDE:
    		{
    			m_current_anim_id = m_use_side_anim_id;
    			m_current_anim_frame_delay = m_use_side_anim_frame_delay;
    			m_current_anim_time_max = m_use_side_anim_time_max;
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
    	m_last_frame = (m_anim_time+time_diff) >= m_current_anim_time_max;
    	m_anim_time = (m_anim_time+time_diff)%m_current_anim_time_max;
    }
};

#endif /* COMPONENTS_CHARACTER_TOPDOWN_VISUALS_H_ */
