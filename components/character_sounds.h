/*
 * character_sounds.h
 *
 *  Created on: Nov 22, 2020
 *      Author: zamfi
 */

#ifndef COMPONENTS_CHARACTER_SOUNDS_H_
#define COMPONENTS_CHARACTER_SOUNDS_H_

#include <iostream>
#include "../types.h"
#include "collision_enums.h"

template<typename ControlT, typename MovementT, typename CollisionT, typename HealthT>
class CharacterSounds
{
public:
    enum class State { IDLE, WALK, JUMP, FALL, ATTACK, HIT, DEAD} ;

    constexpr static Time LONG_IDLE_TIMEOUT = 5000;

    CharacterSounds
	( const SoundID idle_id
	, const SoundID walk_id
	, const SoundID jump_id
	, const SoundID fall_id
	, const SoundID land_id
	, const SoundID attack_id
	, const SoundID hit_id
	, const SoundID dead_id
	, const double volume
	, const EntityID self_id
	, const ComponentAccess<const ControlT>& control_accessor
	, const ComponentAccess<const MovementT>& movement_accessor
	, const ComponentAccess<const CollisionT>& collision_accessor
	, const ComponentAccess<const HealthT>& health_accessor
	)
    : m_self_id(self_id)
    , m_play_new_sound(false)
    , m_current_sound_id(-1)
    , m_idle_id(idle_id)
    , m_walk_id(walk_id)
    , m_jump_id(jump_id)
    , m_fall_id(fall_id)
    , m_land_id(land_id)
    , m_attack_id(attack_id)
    , m_hit_id(hit_id)
    , m_dead_id(dead_id)
    , m_volume(volume)
    , m_state(State::IDLE)
	, m_control_accessor{control_accessor}
	, m_movement_accessor{movement_accessor}
	, m_collision_accessor{collision_accessor}
	, m_health_accessor{health_accessor}
    {}

    template<typename ExtractorF, typename SelfIDObtainerF>
    CharacterSounds
	( ExtractorF&& extract
	, SelfIDObtainerF&& obtain_self_id
	, const ComponentAccess<const ControlT>& control_accessor
	, const ComponentAccess<const MovementT>& movement_accessor
	, const ComponentAccess<const CollisionT>& collision_accessor
	, const ComponentAccess<const HealthT>& health_accessor
	)
	: CharacterSounds
	  { extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().real()
	  , obtain_self_id()
	  , control_accessor
	  , movement_accessor
	  , collision_accessor
	  , health_accessor
	  }
	{}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseCharacterSounds");
    	insert(m_idle_id);
    	insert(m_walk_id);
    	insert(m_jump_id);
    	insert(m_fall_id);
    	insert(m_land_id);
    	insert(m_attack_id);
    	insert(m_hit_id);
    	insert(m_dead_id);
    	insert(m_volume);
    }

    void print(std::ostream& to) const
    {
    	to << "UseCharacterSounds "
		   << m_idle_id << " "
		   << m_walk_id << " "
		   << m_jump_id << " "
		   << m_fall_id << " "
		   << m_land_id << " "
		   << m_attack_id << " "
		   << m_hit_id << " "
		   << m_dead_id << " "
		   << m_volume << " ";
    }

    void set_new_state(const State new_state)
    {
    	m_play_new_sound = true;
    	m_state = new_state;

    	switch(new_state)
    	{
    		case State::IDLE :
    			m_current_sound_id = m_idle_id;
			break;
    		case State::WALK :
    			m_current_sound_id = m_walk_id;
			break;
    		case State::JUMP :
    			m_current_sound_id = m_jump_id;
			break;
    		case State::FALL :
    			m_current_sound_id = m_fall_id;
			break;
    		case State::ATTACK :
    			m_current_sound_id = m_attack_id;
			break;
    		case State::HIT :
    			m_current_sound_id = m_hit_id;
			break;
    		case State::DEAD :
    			m_current_sound_id = m_dead_id;
			break;

    		default:
    			m_current_sound_id = -1;
			break;
    	}
    }

    void update(const Time time_diff)
    {
    	m_play_new_sound = false;

    	const auto& control = m_control_accessor(m_self_id);
    	const auto& movement = m_movement_accessor(m_self_id);
    	const auto& collision = m_collision_accessor(m_self_id);
    	const auto& health = m_health_accessor(m_self_id);

    	switch(m_state)
    	{
    		case State::IDLE:
    			if(health.alive() == false) set_new_state(State::DEAD);
    			else if(health.stunned()) set_new_state(State::HIT);
    			else if(control.decision_attack()) set_new_state(State::ATTACK);
    			else if(collision.standing_on()!=SurfaceType::GROUND && (control.decision_vertical() > 0)) set_new_state(State::JUMP);
    			else if(collision.standing_on()==SurfaceType::GROUND && (control.decision_walk() != 0)) set_new_state(State::WALK);
    			else if(collision.standing_on()==SurfaceType::AIR && movement.vy() < -1) set_new_state(State::FALL);
    		break;

    		case State::WALK:
    			if(health.alive() == false) set_new_state(State::DEAD);
    			else if(health.stunned()) set_new_state(State::HIT);
    			else if(control.decision_attack()) set_new_state(State::ATTACK);
    			else if(collision.standing_on()!=SurfaceType::GROUND && (control.decision_vertical() > 0)) set_new_state(State::JUMP);
    			else if(collision.standing_on()==SurfaceType::GROUND && (control.decision_walk() == 0)) set_new_state(State::IDLE);
    			else if(collision.standing_on()==SurfaceType::AIR && movement.vy() < -1) set_new_state(State::FALL);
    		break;

    		case State::JUMP:
    			if(health.alive() == false) set_new_state(State::DEAD);
    			else if(health.stunned()) set_new_state(State::HIT);
    			else if(control.decision_attack()) set_new_state(State::ATTACK);
    			else if(collision.standing_on()==SurfaceType::GROUND && control.decision_walk() != 0) set_new_state(State::WALK);
    			else if(collision.standing_on()==SurfaceType::GROUND && control.decision_walk() == 0) set_new_state(State::IDLE);
    			else if(collision.standing_on()==SurfaceType::AIR && movement.vy() < -1) set_new_state(State::FALL);
    		break;

    		case State::FALL:
    			if(health.alive() == false) set_new_state(State::DEAD);
    			else if(health.stunned()) set_new_state(State::HIT);
    			else if(control.decision_attack()) set_new_state(State::ATTACK);
    			else if(collision.standing_on()==SurfaceType::GROUND && control.decision_walk() != 0) set_new_state(State::WALK);
    			else if(collision.standing_on()==SurfaceType::GROUND && control.decision_walk() == 0) set_new_state(State::IDLE);
    		break;

    		case State::ATTACK:
    			if(health.alive() == false) set_new_state(State::DEAD);
    			else if(health.stunned()) set_new_state(State::HIT);
    			else if(collision.standing_on()==SurfaceType::AIR && movement.vy() < -1) set_new_state(State::FALL);
    			else if(collision.standing_on()==SurfaceType::GROUND && (control.decision_vertical() > 0)) set_new_state(State::JUMP);
    			else if(collision.standing_on()==SurfaceType::GROUND && (control.decision_walk() != 0)) set_new_state(State::WALK);
    			else set_new_state(State::IDLE);
    		break;

    		case State::HIT:
    			if(health.alive() == false) set_new_state(State::DEAD);
    			else if(control.decision_attack()) set_new_state(State::ATTACK);
    			else if(collision.standing_on()==SurfaceType::AIR && movement.vy() < -1) set_new_state(State::FALL);
    			else if(collision.standing_on()==SurfaceType::GROUND && (control.decision_vertical() > 0)) set_new_state(State::JUMP);
    			else if(collision.standing_on()==SurfaceType::GROUND && (control.decision_walk() != 0)) set_new_state(State::WALK);
    			else if(collision.standing_on()==SurfaceType::GROUND && (control.decision_walk() == 0)) set_new_state(State::IDLE);
    		break;

    		case State::DEAD:
    			//no new state
    		break;

    		default:
    		break;
    	}
    }

    SoundID id() const { return m_current_sound_id; }
    bool changed() const { return m_play_new_sound; }
    double volume() const { return m_volume; }

    EntityID m_self_id;

private:
    bool m_play_new_sound;
    SoundID m_current_sound_id;
    SoundID m_idle_id, m_walk_id, m_jump_id, m_fall_id, m_land_id, m_attack_id, m_hit_id, m_dead_id;
    double m_volume;

    State m_state;
    ComponentAccess<const ControlT> m_control_accessor;
    ComponentAccess<const MovementT> m_movement_accessor;
    ComponentAccess<const CollisionT> m_collision_accessor;
    ComponentAccess<const HealthT> m_health_accessor;
};

#endif /* COMPONENTS_CHARACTER_SOUNDS_H_ */
