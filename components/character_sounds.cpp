/*
 * character_sounds.cpp
 *
 *  Created on: Dec 3, 2021
 *      Author: zamfi
 */

#include "character_sounds.h"
#include "control.h"
#include "movement.h"
#include "collision.h"
#include "health.h"

void CharacterSounds::update(const Time)
{
	m_play_new_sound = false;

	const Control& control = m_control_accessor(m_self_id);
	const Movement& movement = m_movement_accessor(m_self_id);
	const Collision& collision = m_collision_accessor(m_self_id);
	const Health& health = m_health_accessor(m_self_id);

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

