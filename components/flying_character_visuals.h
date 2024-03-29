/*
 * flying_character_visuals.h
 *
 *  Created on: Jun 15, 2021
 *      Author: zamfi
 */

#ifndef COMPONENTS_FLYING_CHARACTER_VISUALS_H_
#define COMPONENTS_FLYING_CHARACTER_VISUALS_H_


#include "visuals_enums.h"
#include "../types.h"
#include "collision_enums.h"

template<typename ControlT, typename CollisionT, typename HealthT>
class FlyingCharacterVisuals
{
public:
    enum class RenderStates { LAND_IDLE, FLY_IDLE, FLY_SIDE, FLY_UP, FLY_DOWN, ATTACK, HIT, DEAD};

    template<typename AnimationAccessorT>
    FlyingCharacterVisuals
	( const AnimationID land_idle_anim_id
	, const AnimationID fly_idle_anim_id
	, const AnimationID fly_side_anim_id
	, const AnimationID fly_up_anim_id
	, const AnimationID fly_down_anim_id
  	, const AnimationID attack_anim_id
	, const AnimationID hit_anim_id
	, const AnimationID dead_anim_id
	, const AnimationAccessorT& animation_access
	, const EntityID self_id
	, ComponentAccess<const ControlT> control_accessor
	, ComponentAccess<const CollisionT> collision_accessor
	, ComponentAccess<const HealthT> health_accessor
  )
	: m_current_state(RenderStates::LAND_IDLE)
	, m_current_anim_id{land_idle_anim_id}
	, m_land_idle_anim_id{land_idle_anim_id}
	, m_fly_idle_anim_id{fly_idle_anim_id}
	, m_fly_side_anim_id{fly_side_anim_id}
	, m_fly_up_anim_id{fly_up_anim_id}
	, m_fly_down_anim_id{fly_down_anim_id}
	, m_attack_anim_id{attack_anim_id}
	, m_hit_anim_id{hit_anim_id}
	, m_dead_anim_id{dead_anim_id}
	, m_current_anim_frame_delay{1}
	, m_land_idle_anim_frame_delay{1}
	, m_fly_idle_anim_frame_delay{1}
	, m_fly_side_anim_frame_delay{1}
	, m_fly_up_anim_frame_delay{1}
	, m_fly_down_anim_frame_delay{1}
	, m_attack_anim_frame_delay{1}
	, m_hit_anim_frame_delay{1}
	, m_dead_anim_frame_delay{1}
	, m_current_anim_time_max{1}
	, m_land_idle_anim_time_max{1}
	, m_fly_idle_anim_time_max{1}
	, m_fly_side_anim_time_max{1}
	, m_fly_up_anim_time_max{1}
	, m_fly_down_anim_time_max{1}
	, m_attack_anim_time_max{1}
	, m_hit_anim_time_max{1}
	, m_dead_anim_time_max{1}
	, m_anim_time{0}
	, m_last_frame{false}
	, m_look_dir_x{1.0}
	, m_look_dir_y{0.0}
	, m_layer{VisualLayer::ACTION}
	, m_self_id{self_id}
	, m_control_accessor{std::move(control_accessor)}
	, m_collision_accessor{std::move(collision_accessor)}
	, m_health_accessor{std::move(health_accessor)}
	{
		const auto& land_idle_anim_opt = animation_access(land_idle_anim_id);

		if(land_idle_anim_opt)
		{
			m_land_idle_anim_frame_delay = land_idle_anim_opt->get().frame_delay_ms();
			m_land_idle_anim_time_max = m_land_idle_anim_frame_delay*land_idle_anim_opt->get().frame_count();
		}
		else
		{ /*error land_idle_anim_id*/ }

		const auto& fly_idle_anim_opt = animation_access(fly_idle_anim_id);

		if(fly_idle_anim_opt)
		{
			m_fly_idle_anim_frame_delay = fly_idle_anim_opt->get().frame_delay_ms();
			m_fly_idle_anim_time_max = m_fly_idle_anim_frame_delay*fly_idle_anim_opt->get().frame_count();
		}
		else
		{ /*error fly_idle_anim_id*/ }

		const auto& fly_side_anim_opt = animation_access(fly_side_anim_id);

		if(fly_side_anim_opt)
		{
			m_fly_side_anim_frame_delay = fly_side_anim_opt->get().frame_delay_ms();
			m_fly_side_anim_time_max = m_fly_side_anim_frame_delay*fly_side_anim_opt->get().frame_count();
		}
		else
		{ /*error fly_side_anim_id*/ }

		const auto& fly_up_anim_opt = animation_access(fly_up_anim_id);

		if(fly_up_anim_opt)
		{
			m_fly_up_anim_frame_delay = fly_up_anim_opt->get().frame_delay_ms();
			m_fly_up_anim_time_max = m_fly_up_anim_frame_delay*fly_up_anim_opt->get().frame_count();
		}
		else
		{ /*error fly_up_anim_id*/ }

		const auto& fly_down_anim_opt = animation_access(fly_down_anim_id);

		if(fly_down_anim_opt)
		{
			m_fly_down_anim_frame_delay = fly_down_anim_opt->get().frame_delay_ms();
			m_fly_down_anim_time_max = m_fly_down_anim_frame_delay*fly_down_anim_opt->get().frame_count();
		}
		else
		{ /*error fly_down_anim_id*/ }

		const auto& attack_anim_opt = animation_access(attack_anim_id);

		if(attack_anim_opt)
		{
			m_attack_anim_frame_delay = attack_anim_opt->get().frame_delay_ms();
			m_attack_anim_time_max = m_attack_anim_frame_delay*attack_anim_opt->get().frame_count();
		}
		else
		{ /*error attack_anim_id*/ }

		const auto& hit_anim_opt = animation_access(hit_anim_id);

		if(hit_anim_opt)
		{
			m_hit_anim_frame_delay = hit_anim_opt->get().frame_delay_ms();
			m_hit_anim_time_max = m_hit_anim_frame_delay*hit_anim_opt->get().frame_count();
		}
		else
		{ /*error hit_anim_id*/ }

		const auto& dead_anim_opt = animation_access(dead_anim_id);

		if(dead_anim_opt)
		{
			m_dead_anim_frame_delay = dead_anim_opt->get().frame_delay_ms();
			m_dead_anim_time_max = m_dead_anim_frame_delay*dead_anim_opt->get().frame_count();
		}
		else
		{ /*error dead_anim_id*/ }

		set_new_state(RenderStates::LAND_IDLE);
	}

    template<typename ExtractorF, typename AnimationAccessorT, typename SelfIDObtainerF>
	FlyingCharacterVisuals
	( ExtractorF&& extract
	, const AnimationAccessorT& animation_access
	, const SelfIDObtainerF& obtain_self_id
	, ComponentAccess<const ControlT> control_accessor
	, ComponentAccess<const CollisionT> collision_accessor
	, ComponentAccess<const HealthT> health_accessor
	)
	: FlyingCharacterVisuals
	  { extract()
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
	  , std::move(collision_accessor)
	  , std::move(health_accessor)
	  }
	{}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseFlyingCharacterVisuals");
    	insert(m_land_idle_anim_id);
    	insert(m_fly_idle_anim_id);
    	insert(m_fly_side_anim_id);
    	insert(m_fly_up_anim_id);
    	insert(m_fly_down_anim_id);
    	insert(m_attack_anim_id);
    	insert(m_hit_anim_id);
    	insert(m_dead_anim_id);
    }

    void update_animation(const Time time_diff)
    {
    	const auto& control = m_control_accessor(m_self_id);
    	const auto& collision = m_collision_accessor(m_self_id);
    	const auto& health = m_health_accessor(m_self_id);

    	if(control.decision_vertical() != 0 || control.decision_walk() != 0)
    	{
    		m_look_dir_x = control.decision_walk();
    		m_look_dir_y = control.decision_vertical();
    	}

    	switch(m_current_state)
    	{
    		default:
    		case RenderStates::LAND_IDLE:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(health.stunned()) set_new_state(RenderStates::HIT);
    			else if(control.decision_attack()) set_new_state(RenderStates::ATTACK);
    			else if(control.decision_walk() != 0) set_new_state(RenderStates::FLY_SIDE);
    			else if(control.decision_vertical() > 0) set_new_state(RenderStates::FLY_UP);
    			else if(control.decision_vertical() < 0) set_new_state(RenderStates::FLY_DOWN);
    			else if(collision.standing_on()==SurfaceType::AIR) set_new_state(RenderStates::FLY_IDLE);
    			else advance_animation(time_diff);
    		break;

    		case RenderStates::FLY_IDLE:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(health.stunned()) set_new_state(RenderStates::HIT);
    			else if(control.decision_attack()) set_new_state(RenderStates::ATTACK);
    			else if(control.decision_walk() != 0) set_new_state(RenderStates::FLY_SIDE);
    			else if(control.decision_vertical() > 0) set_new_state(RenderStates::FLY_UP);
    			else if(control.decision_vertical() < 0) set_new_state(RenderStates::FLY_DOWN);
    			else if(collision.standing_on()==SurfaceType::GROUND) set_new_state(RenderStates::LAND_IDLE);
    			else advance_animation(time_diff);
    		break;

    		case RenderStates::FLY_SIDE:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(health.stunned()) set_new_state(RenderStates::HIT);
    			else if(control.decision_attack()) set_new_state(RenderStates::ATTACK);
    			else if(control.decision_walk() != 0) advance_animation(time_diff);
    			else if(control.decision_vertical() > 0) set_new_state(RenderStates::FLY_UP);
    			else if(control.decision_vertical() < 0) set_new_state(RenderStates::FLY_DOWN);
    			else if(collision.standing_on()==SurfaceType::AIR) set_new_state(RenderStates::FLY_IDLE);
    			else set_new_state(RenderStates::LAND_IDLE);
    		break;

    		case RenderStates::FLY_UP:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(health.stunned()) set_new_state(RenderStates::HIT);
    			else if(control.decision_attack()) set_new_state(RenderStates::ATTACK);
    			else if(control.decision_walk() != 0) set_new_state(RenderStates::FLY_SIDE);
    			else if(control.decision_vertical() > 0) advance_animation(time_diff);
    			else if(control.decision_vertical() < 0) set_new_state(RenderStates::FLY_DOWN);
    			else if(collision.standing_on()==SurfaceType::AIR) set_new_state(RenderStates::FLY_IDLE);
    			else set_new_state(RenderStates::LAND_IDLE);
    		break;

    		case RenderStates::FLY_DOWN:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(health.stunned()) set_new_state(RenderStates::HIT);
    			else if(control.decision_attack()) set_new_state(RenderStates::ATTACK);
    			else if(control.decision_walk() != 0) set_new_state(RenderStates::FLY_SIDE);
    			else if(control.decision_vertical() > 0) set_new_state(RenderStates::FLY_UP);
    			else if(control.decision_vertical() < 0) advance_animation(time_diff);
    			else if(collision.standing_on()==SurfaceType::AIR) set_new_state(RenderStates::FLY_IDLE);
    			else set_new_state(RenderStates::LAND_IDLE);
    		break;

    		case RenderStates::ATTACK:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(health.stunned()) set_new_state(RenderStates::HIT);
    			else if(m_last_frame && (control.decision_walk() != 0)) set_new_state(RenderStates::FLY_SIDE);
    			else if(m_last_frame && (control.decision_vertical() > 0)) set_new_state(RenderStates::FLY_UP);
    			else if(m_last_frame && (control.decision_vertical() < 0)) set_new_state(RenderStates::FLY_DOWN);
    			else if(m_last_frame && (collision.standing_on()==SurfaceType::AIR)) set_new_state(RenderStates::FLY_IDLE);
    			else if(m_last_frame) set_new_state(RenderStates::LAND_IDLE);
    			else advance_animation(time_diff);
    		break;

    		case RenderStates::HIT:
    			if(health.alive() == false) set_new_state(RenderStates::DEAD);
    			else if(m_last_frame && control.decision_attack()) set_new_state(RenderStates::ATTACK);
    			else if(m_last_frame && (control.decision_walk() != 0)) set_new_state(RenderStates::FLY_SIDE);
    			else if(m_last_frame && (control.decision_vertical() > 0)) set_new_state(RenderStates::FLY_UP);
    			else if(m_last_frame && (control.decision_vertical() < 0)) set_new_state(RenderStates::FLY_DOWN);
    			else if(m_last_frame && (collision.standing_on()==SurfaceType::AIR)) set_new_state(RenderStates::FLY_IDLE);
    			else if(m_last_frame) set_new_state(RenderStates::LAND_IDLE);
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
    AnimationID m_land_idle_anim_id;
	AnimationID m_fly_idle_anim_id;
	AnimationID m_fly_side_anim_id;
	AnimationID m_fly_up_anim_id;
	AnimationID m_fly_down_anim_id;
	AnimationID m_attack_anim_id;
	AnimationID m_hit_anim_id;
	AnimationID m_dead_anim_id;
    int m_current_anim_frame_delay;
    int m_land_idle_anim_frame_delay;
    int m_fly_idle_anim_frame_delay;
    int m_fly_side_anim_frame_delay;
    int m_fly_up_anim_frame_delay;
    int m_fly_down_anim_frame_delay;
    int m_attack_anim_frame_delay;
    int m_hit_anim_frame_delay;
    int m_dead_anim_frame_delay;
    int m_current_anim_time_max;
    int m_land_idle_anim_time_max;
    int m_fly_idle_anim_time_max;
    int m_fly_side_anim_time_max;
    int m_fly_up_anim_time_max;
    int m_fly_down_anim_time_max;
    int m_attack_anim_time_max;
    int m_hit_anim_time_max;
    int m_dead_anim_time_max;
    int m_anim_time;
    bool m_last_frame;
    double m_look_dir_x;
    double m_look_dir_y;
    VisualLayer m_layer;
    EntityID m_self_id;
    ComponentAccess<const ControlT> m_control_accessor;
    ComponentAccess<const CollisionT> m_collision_accessor;
    ComponentAccess<const HealthT> m_health_accessor;

    void set_new_state(RenderStates new_state)
    {
		switch(new_state)
    	{
    		default:
    		case RenderStates::LAND_IDLE:
    		{
    			m_current_anim_id = m_land_idle_anim_id;
    			m_current_anim_frame_delay = m_land_idle_anim_frame_delay;
    			m_current_anim_time_max = m_land_idle_anim_time_max;
    		}
    		break;

    		case RenderStates::FLY_IDLE:
    		{
    			m_current_anim_id = m_fly_idle_anim_id;
    			m_current_anim_frame_delay = m_fly_idle_anim_frame_delay;
    			m_current_anim_time_max = m_fly_idle_anim_time_max;
    		}
    		break;

    		case RenderStates::FLY_SIDE:
    		{
    			m_current_anim_id = m_fly_side_anim_id;
    			m_current_anim_frame_delay = m_fly_side_anim_frame_delay;
    			m_current_anim_time_max = m_fly_side_anim_time_max;
    		}
    		break;

    		case RenderStates::FLY_UP:
    		{
    			m_current_anim_id = m_fly_up_anim_id;
    			m_current_anim_frame_delay = m_fly_up_anim_frame_delay;
    			m_current_anim_time_max = m_fly_up_anim_time_max;
    		}
    		break;

    		case RenderStates::FLY_DOWN:
    		{
    			m_current_anim_id = m_fly_down_anim_id;
    			m_current_anim_frame_delay = m_fly_down_anim_frame_delay;
    			m_current_anim_time_max = m_fly_down_anim_time_max;
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




#endif /* COMPONENTS_FLYING_CHARACTER_VISUALS_H_ */
