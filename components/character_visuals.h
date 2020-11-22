/*
 * character_visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_CHARACTER_VISUALS_H_
#define COMPONENTS_CHARACTER_VISUALS_H_

#include "visuals.h"
#include "../systems/resource_system.h"
#include "control.h"
#include "movement.h"
#include "collision.h"
#include "health.h"

template<typename EntitySystemT>
class CharacterVisuals : public Visuals
{
public:
	using Base = Visuals;
    static const unsigned int ANIMATION_DELAY_MS = 50;
    enum class RenderStates { IDLE, WALK, JUMP, FALL, ATTACK, HIT, DEAD};

    CharacterVisuals(SpritesheetID spr_id, const EntityID self_id, ResourceSystem& resource_system, EntitySystemT& entity_system)
    : m_self_id(self_id)
    , m_current_state(RenderStates::IDLE)
    , m_animation_count(0)
    , m_animation_time(0)
    , m_spritesheet_id(spr_id)
    , m_layer(VisualLayer::ACTION)
    , m_animation_state_size(1)
	, m_animation_state_offset(0)
    , m_resource_system(resource_system)
    , m_entity_system(entity_system)
    {}

    void print(std::ostream& to) const
    {
    	to << "UseCharacterVisuals "
    	   << m_spritesheet_id<< " ";
    }

    void update_animation(const Time time_diff)
    {
    	const auto& control = m_entity_system.entity_component(m_self_id, (Control*)nullptr);
    	const auto& movement = m_entity_system.entity_component(m_self_id, (Movement*)nullptr);
    	const auto& collision = m_entity_system.entity_component(m_self_id, (Collision*)nullptr);
    	const auto& health = m_entity_system.entity_component(m_self_id, (Health*)nullptr);

    	switch(m_current_state)
		{
			case RenderStates::IDLE:
				if(health.alive() == false) set_new_state(RenderStates::DEAD);
				else if(health.stunned()) set_new_state(RenderStates::HIT);
				else if(control.decision_attack()) set_new_state(RenderStates::ATTACK);
				else if(collision.standing_on()!=Collision::SurfaceType::GROUND && (control.decision_vertical() > 0)) set_new_state(RenderStates::JUMP);
				else if(collision.standing_on()==Collision::SurfaceType::GROUND && (control.decision_walk() != 0)) set_new_state(RenderStates::WALK);
				else if(collision.standing_on()==Collision::SurfaceType::AIR && movement.vy() < -1) set_new_state(RenderStates::FALL);
				else advance_animation(time_diff);
			break;

			case RenderStates::WALK:
				if(health.alive() == false) set_new_state(RenderStates::DEAD);
				else if(health.stunned()) set_new_state(RenderStates::HIT);
				else if(control.decision_attack()) set_new_state(RenderStates::ATTACK);
				else if(collision.standing_on()!=Collision::SurfaceType::GROUND && (control.decision_vertical() > 0)) set_new_state(RenderStates::JUMP);
				else if(collision.standing_on()==Collision::SurfaceType::GROUND && (control.decision_walk() == 0)) set_new_state(RenderStates::IDLE);
				else if(collision.standing_on()==Collision::SurfaceType::AIR && movement.vy() < -1) set_new_state(RenderStates::FALL);
				else advance_animation(time_diff);
			break;

			case RenderStates::JUMP:
				if(health.alive() == false) set_new_state(RenderStates::DEAD);
				else if(health.stunned()) set_new_state(RenderStates::HIT);
				else if(control.decision_attack()) set_new_state(RenderStates::ATTACK);
				else if(collision.standing_on()==Collision::SurfaceType::GROUND && control.decision_walk() != 0) set_new_state(RenderStates::WALK);
				else if(collision.standing_on()==Collision::SurfaceType::GROUND && control.decision_walk() == 0) set_new_state(RenderStates::IDLE);
				else if(collision.standing_on()==Collision::SurfaceType::AIR && movement.vy() < -1 && animation_count_max()) set_new_state(RenderStates::FALL);
				else advance_animation(time_diff);
			break;

			case RenderStates::FALL:
				if(health.alive() == false) set_new_state(RenderStates::DEAD);
				else if(health.stunned()) set_new_state(RenderStates::HIT);
				else if(control.decision_attack()) set_new_state(RenderStates::ATTACK);
				else if(collision.standing_on()==Collision::SurfaceType::GROUND && control.decision_walk() != 0) set_new_state(RenderStates::WALK);
				else if(collision.standing_on()==Collision::SurfaceType::GROUND && control.decision_walk() == 0) set_new_state(RenderStates::IDLE);
				else advance_animation(time_diff);
			break;

			case RenderStates::ATTACK:
				if(health.alive() == false) set_new_state(RenderStates::DEAD);
				else if(health.stunned()) set_new_state(RenderStates::HIT);
				else if(animation_count_max() && collision.standing_on()==Collision::SurfaceType::AIR && movement.vy() < -1) set_new_state(RenderStates::FALL);
				else if(animation_count_max() && collision.standing_on()==Collision::SurfaceType::GROUND && (control.decision_vertical() > 0)) set_new_state(RenderStates::JUMP);
				else if(animation_count_max() && collision.standing_on()==Collision::SurfaceType::GROUND && (control.decision_walk() != 0)) set_new_state(RenderStates::WALK);
				else if(animation_count_max()) set_new_state(RenderStates::IDLE);
				else advance_animation(time_diff);
			break;

			case RenderStates::HIT:
				if(health.alive() == false) set_new_state(RenderStates::DEAD);
				else if(animation_count_max() && control.decision_attack()) set_new_state(RenderStates::ATTACK);
				else if(animation_count_max() && collision.standing_on()==Collision::SurfaceType::AIR && movement.vy() < -1) set_new_state(RenderStates::FALL);
				else if(animation_count_max() && collision.standing_on()==Collision::SurfaceType::GROUND && (control.decision_vertical() > 0)) set_new_state(RenderStates::JUMP);
				else if(animation_count_max() && collision.standing_on()==Collision::SurfaceType::GROUND && (control.decision_walk() != 0)) set_new_state(RenderStates::WALK);
				else if(animation_count_max() && collision.standing_on()==Collision::SurfaceType::GROUND && (control.decision_walk() == 0)) set_new_state(RenderStates::IDLE);
				else advance_animation(time_diff);
			break;

			case RenderStates::DEAD:
				if(animation_count_max() == false)
					advance_animation(time_diff);
				//else do nothing
			break;

			default:
				advance_animation(time_diff);
			break;
		}
    }

    uint8_t animation_sprite(uint16_t rx, uint16_t ry) const
    {
        return m_animation_state_offset + m_animation_count;
    }

    SpritesheetID spritesheet_id() { return m_spritesheet_id; }
    void set_spritesheet_id(SpritesheetID spr_id) { m_spritesheet_id = spr_id; }

    uint16_t repeat_x() const { return 1; }
    uint16_t repeat_y() const { return 1; }
    void set_repeat_x(uint16_t val) {}
    void set_repeat_y(uint16_t val) {}
    VisualLayer layer() const { return m_layer; }
    void set_layer(VisualLayer val) { m_layer = val; }

    EntityID m_self_id;

private:
    RenderStates m_current_state;
    uint8_t m_animation_count;
    double m_animation_time;
    SpritesheetID m_spritesheet_id;
    VisualLayer m_layer;
    int m_animation_state_size, m_animation_state_offset;
    ResourceSystem& m_resource_system;
    EntitySystemT& m_entity_system;

    void set_new_state(RenderStates new_state)
    {
        m_current_state = new_state;
        m_animation_count = 0;
        m_animation_time = 0;
        m_animation_state_size = animation_state_size();
        m_animation_state_offset = animation_state_offset();
    }

    void advance_animation(Time time_diff)
    {
        m_animation_time += time_diff;
        if(m_animation_time >= ANIMATION_DELAY_MS)
        {
            m_animation_time -= ANIMATION_DELAY_MS;
    		m_animation_count = (m_animation_count+1)%m_animation_state_size;
        }
    }

    bool animation_count_max() const
    {
        return (m_animation_count == m_animation_state_size-1);
    }

    uint8_t animation_state_offset() const
    {
        switch(m_current_state)
        {
            case RenderStates::IDLE:
                return m_resource_system.spritesheet(m_spritesheet_id)->idle_sprite_start();
            case RenderStates::WALK:
                return m_resource_system.spritesheet(m_spritesheet_id)->walk_sprite_start();
            case RenderStates::JUMP:
                return m_resource_system.spritesheet(m_spritesheet_id)->jump_sprite_start();
            case RenderStates::FALL:
                return m_resource_system.spritesheet(m_spritesheet_id)->fall_sprite_start();
            case RenderStates::ATTACK:
                return m_resource_system.spritesheet(m_spritesheet_id)->attack_sprite_start();
            case RenderStates::HIT:
                return m_resource_system.spritesheet(m_spritesheet_id)->hit_sprite_start();
            case RenderStates::DEAD:
                return m_resource_system.spritesheet(m_spritesheet_id)->dead_sprite_start();
            default:
                return 0;
        }
    }

    uint8_t animation_state_size() const
    {
        switch(m_current_state)
        {
            case RenderStates::IDLE:
            	return m_resource_system.spritesheet(m_spritesheet_id)->idle_sprite_size();
            case RenderStates::WALK:
            	return m_resource_system.spritesheet(m_spritesheet_id)->walk_sprite_size();
            case RenderStates::JUMP:
            	return m_resource_system.spritesheet(m_spritesheet_id)->jump_sprite_size();
            case RenderStates::FALL:
            	return m_resource_system.spritesheet(m_spritesheet_id)->fall_sprite_size();
            case RenderStates::ATTACK:
            	return m_resource_system.spritesheet(m_spritesheet_id)->attack_sprite_size();
            case RenderStates::HIT:
            	return m_resource_system.spritesheet(m_spritesheet_id)->hit_sprite_size();
            case RenderStates::DEAD:
            	return m_resource_system.spritesheet(m_spritesheet_id)->dead_sprite_size();
            default:
            	return 0;
        }
    }
};

#endif /* COMPONENTS_CHARACTER_VISUALS_H_ */
