/*
 * character_sounds.h
 *
 *  Created on: Nov 22, 2020
 *      Author: zamfi
 */

#ifndef COMPONENTS_CHARACTER_SOUNDS_H_
#define COMPONENTS_CHARACTER_SOUNDS_H_

#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "../types.h"

class Control;
class Movement;
class Collision;
class Health;

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
	, const ComponentAccess<const Control>& control_accessor
	, const ComponentAccess<const Movement>& movement_accessor
	, const ComponentAccess<const Collision>& collision_accessor
	, const ComponentAccess<const Health>& health_accessor
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

    template<typename ExtractorF, typename SelfIDF>
    CharacterSounds
	( ExtractorF&& extract
	, SelfIDF&& obtain_self_id
	, const ComponentAccess<const Control>& control_accessor
	, const ComponentAccess<const Movement>& movement_accessor
	, const ComponentAccess<const Collision>& collision_accessor
	, const ComponentAccess<const Health>& health_accessor
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

    void update(const Time time_diff);
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
    ComponentAccess<const Control> m_control_accessor;
    ComponentAccess<const Movement> m_movement_accessor;
    ComponentAccess<const Collision> m_collision_accessor;
    ComponentAccess<const Health> m_health_accessor;
};

#endif /* COMPONENTS_CHARACTER_SOUNDS_H_ */
