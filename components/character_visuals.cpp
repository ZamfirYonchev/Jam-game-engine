/*
 * character_visuals.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "character_visuals.h"
#include "../globals.h"

uint8_t CharacterVisuals::animation_state_size() const
{
    switch(m_current_state)
    {
        case IDLE:
        	return globals.resource_system.spritesheet(m_spritesheet_id)->idle_sprite_size();
        case WALK:
        	return globals.resource_system.spritesheet(m_spritesheet_id)->walk_sprite_size();
        case JUMP:
        	return globals.resource_system.spritesheet(m_spritesheet_id)->jump_sprite_size();
        case FALL:
        	return globals.resource_system.spritesheet(m_spritesheet_id)->fall_sprite_size();
        case ATTACK:
        	return globals.resource_system.spritesheet(m_spritesheet_id)->attack_sprite_size();
        case HIT:
        	return globals.resource_system.spritesheet(m_spritesheet_id)->hit_sprite_size();
        case DEAD:
        	return globals.resource_system.spritesheet(m_spritesheet_id)->dead_sprite_size();
        default:
        	return 0;
    }
}

uint8_t CharacterVisuals::animation_state_offset() const
{
    switch(m_current_state)
    {
        case IDLE:
            return globals.resource_system.spritesheet(m_spritesheet_id)->idle_sprite_start();
        case WALK:
            return globals.resource_system.spritesheet(m_spritesheet_id)->walk_sprite_start();
        case JUMP:
            return globals.resource_system.spritesheet(m_spritesheet_id)->jump_sprite_start();
        case FALL:
            return globals.resource_system.spritesheet(m_spritesheet_id)->fall_sprite_start();
        case ATTACK:
            return globals.resource_system.spritesheet(m_spritesheet_id)->attack_sprite_start();
        case HIT:
            return globals.resource_system.spritesheet(m_spritesheet_id)->hit_sprite_start();
        case DEAD:
            return globals.resource_system.spritesheet(m_spritesheet_id)->dead_sprite_start();
        default:
            return 0;
    }
}


