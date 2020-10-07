/*
 * add_zone_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_zone_command.h"
#include "../entity.h"
#include "../components/absolute_position.h"
#include "../components/basic_collision.h"
#include "../components/trigger_interaction.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

void AddZoneCommand::execute() const
{
	Entity& entity = system<EntitySystem>().add_new_entity();
	entity.set_component<AbsolutePosition>(m_x, m_y, m_w, m_h);
    entity.set_component<BasicCollision>(Collision::TRANSPARENT, 1.0);
    entity.set_component<TriggerInteraction>(m_trigger_group, m_on_enter_proc_id_self, m_on_enter_proc_id_other, m_on_exit_proc_id_self);
    system<EntitySystem>().add_accessed_entity(entity.id());
}


