/*
 * character_visuals.cpp
 *
 *  Created on: Dec 3, 2021
 *      Author: zamfi
 */

#include "character_visuals.h"
#include "control.h"
#include "movement.h"
#include "collision.h"
#include "health.h"

void CharacterVisuals::update_animation(const Time time_diff)
{
	const Control& control = m_control_accessor(m_self_id);
	const Movement& movement = m_movement_accessor(m_self_id);
	const Collision& collision = m_collision_accessor(m_self_id);
	const Health& health = m_health_accessor(m_self_id);

	switch(m_current_state)
	{
		default:
		case RenderStates::IDLE:
			if(health.alive() == false) set_new_state(RenderStates::DEAD);
			else if(health.stunned()) set_new_state(RenderStates::HIT);
			else if(control.decision_attack()) set_new_state(RenderStates::ATTACK);
			else if(collision.standing_on()!=SurfaceType::GROUND && (control.decision_vertical() > 0)) set_new_state(RenderStates::JUMP);
			else if(collision.standing_on()==SurfaceType::GROUND && (control.decision_walk() != 0)) set_new_state(RenderStates::WALK);
			else if(collision.standing_on()==SurfaceType::AIR && movement.vy() < 0) set_new_state(RenderStates::FALL);
			else advance_animation(time_diff);
		break;

		case RenderStates::WALK:
			if(health.alive() == false) set_new_state(RenderStates::DEAD);
			else if(health.stunned()) set_new_state(RenderStates::HIT);
			else if(control.decision_attack()) set_new_state(RenderStates::ATTACK);
			else if(collision.standing_on()!=SurfaceType::GROUND && (control.decision_vertical() > 0)) set_new_state(RenderStates::JUMP);
			else if(collision.standing_on()==SurfaceType::GROUND && (control.decision_walk() == 0)) set_new_state(RenderStates::IDLE);
			else if(collision.standing_on()==SurfaceType::AIR && movement.vy() < 0) set_new_state(RenderStates::FALL);
			else advance_animation(time_diff);
		break;

		case RenderStates::JUMP:
			if(health.alive() == false) set_new_state(RenderStates::DEAD);
			else if(health.stunned()) set_new_state(RenderStates::HIT);
			else if(control.decision_attack()) set_new_state(RenderStates::ATTACK);
			else if(collision.standing_on()==SurfaceType::GROUND && control.decision_walk() != 0) set_new_state(RenderStates::WALK);
			else if(collision.standing_on()==SurfaceType::GROUND && control.decision_walk() == 0) set_new_state(RenderStates::IDLE);
			else if(collision.standing_on()==SurfaceType::AIR && movement.vy() < 0 && m_last_frame) set_new_state(RenderStates::FALL);
			else advance_animation(time_diff);
		break;

		case RenderStates::FALL:
			if(health.alive() == false) set_new_state(RenderStates::DEAD);
			else if(health.stunned()) set_new_state(RenderStates::HIT);
			else if(control.decision_attack()) set_new_state(RenderStates::ATTACK);
			else if(collision.standing_on()==SurfaceType::GROUND && control.decision_walk() != 0) set_new_state(RenderStates::WALK);
			else if(collision.standing_on()==SurfaceType::GROUND && control.decision_walk() == 0) set_new_state(RenderStates::IDLE);
			else advance_animation(time_diff);
		break;

		case RenderStates::ATTACK:
			if(health.alive() == false) set_new_state(RenderStates::DEAD);
			else if(health.stunned()) set_new_state(RenderStates::HIT);
			else if(m_last_frame && collision.standing_on()==SurfaceType::AIR && movement.vy() < 0) set_new_state(RenderStates::FALL);
			else if(m_last_frame && collision.standing_on()==SurfaceType::GROUND && (control.decision_vertical() > 0)) set_new_state(RenderStates::JUMP);
			else if(m_last_frame && collision.standing_on()==SurfaceType::GROUND && (control.decision_walk() != 0)) set_new_state(RenderStates::WALK);
			else if(m_last_frame) set_new_state(RenderStates::IDLE);
			else advance_animation(time_diff);
		break;

		case RenderStates::HIT:
			if(health.alive() == false) set_new_state(RenderStates::DEAD);
			else if(m_last_frame && control.decision_attack()) set_new_state(RenderStates::ATTACK);
			else if(m_last_frame && collision.standing_on()==SurfaceType::AIR && movement.vy() < 0) set_new_state(RenderStates::FALL);
			else if(m_last_frame && collision.standing_on()==SurfaceType::GROUND && (control.decision_vertical() > 0)) set_new_state(RenderStates::JUMP);
			else if(m_last_frame && collision.standing_on()==SurfaceType::GROUND && (control.decision_walk() != 0)) set_new_state(RenderStates::WALK);
			else if(m_last_frame && collision.standing_on()==SurfaceType::GROUND && (control.decision_walk() == 0)) set_new_state(RenderStates::IDLE);
			else advance_animation(time_diff);
		break;

		case RenderStates::DEAD:
			if(m_last_frame == false)
				advance_animation(time_diff);
			//else do nothing
		break;
	}
}
