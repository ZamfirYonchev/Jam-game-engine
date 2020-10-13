/*
 * add_visual_object_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_visual_object_command.h"
#include "../entity.h"
#include "../components/absolute_position.h"
#include "../components/static_visuals.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

void AddVisualObjectCommand::execute() const
{
	Entity& entity = system<EntitySystem>().add_new_entity();
	entity.set_component<AbsolutePosition>(m_pos);
	entity.set_component<StaticVisuals>(m_spr_id, m_sprite);
    system<EntitySystem>().add_accessed_entity(entity.id());
}
