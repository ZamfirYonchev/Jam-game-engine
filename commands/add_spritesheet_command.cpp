/*
 * add_spritesheet_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_spritesheet_command.h"
#include "../globals.h"

void AddSpritesheetCommand::execute() const
{
	resource_system().addNewSpritesheet(m_idle_start, m_idle_size
                                            , m_walk_start, m_walk_size
                                            , m_jump_start, m_jump_size
                                            , m_fall_start, m_fall_size
                                            , m_attack_start, m_attack_size
                                            , m_hit_start, m_hit_size
                                            , m_dead_start, m_dead_size
                                            , m_scale_factor
                                             );
    globals().access_spritesheet_id = resource_system().last_spritesheet_id();
}
