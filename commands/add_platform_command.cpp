/*
 * add_platform_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_platform_command.h"
#include "../entity.h"
#include "../components/absolute_position.h"
#include "../components/basic_collision.h"
#include "../components/tiled_visuals.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

void AddPlatformCommand::execute() const
{
	Entity& entity = system<EntitySystem>().add_new_entity();
    entity.set_component<AbsolutePosition>(m_pos);
    entity.set_component<BasicCollision>(Collision::SOLID, 1.0);
    entity.set_component<TiledVisuals>(m_spr_id, m_tile_w, m_tile_h, entity.id());
    system<EntitySystem>().add_accessed_entity(entity.id());
}
