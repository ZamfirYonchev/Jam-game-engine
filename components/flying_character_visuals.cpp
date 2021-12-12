/*
 * flying_character_visuals.cpp
 *
 *  Created on: Dec 3, 2021
 *      Author: zamfi
 */

#include "flying_character_visuals.h"
#include "control.h"
#include "collision.h"
#include "health.h"

void FlyingCharacterVisuals::update_animation(const Time time_diff)
{
	const Control& control = m_control_accessor(m_self_id);
	const Collision& collision = m_collision_accessor(m_self_id);
	const Health& health = m_health_accessor(m_self_id);

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
