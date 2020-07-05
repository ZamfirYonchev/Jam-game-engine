/*
 * add_platform_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_platform_command.h"
#include "../globals.h"
#include "../entity.h"
#include "../components/absolute_position.h"
#include "../components/basic_collision.h"
#include "../components/tiled_visuals.h"

void AddPlatformCommand::execute() const
{
	Entity& entity = entity_system().add_new_entity();
    entity.set_position(new AbsolutePosition(m_x, m_y, m_w, m_h));
    entity.set_collision(new BasicCollision(Collision::SOLID));
    entity.set_visuals(new TiledVisuals(m_spr_id, m_tile_w, m_tile_h, entity.id()));
    entity_system().add_accessed_entity(entity.id());
}
