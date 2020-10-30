/*
 * character_visuals.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "character_visuals.h"
#include "../systems/resource_system.h"

uint8_t CharacterVisuals::animation_state_size() const
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

uint8_t CharacterVisuals::animation_state_offset() const
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


