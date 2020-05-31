/*
 * add_zone_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_zone_command.h"
#include "../globals.h"
#include "../entity.h"
#include "../components/absolute_position.h"
#include "../components/basic_collision.h"
#include "../components/trigger_interaction.h"

void AddZoneCommand::execute() const
{
	Entity& entity = entity_system().add_new_entity();
	entity.set_position(new AbsolutePosition(m_x, m_y, m_w, m_h));
    entity.set_collision(new BasicCollision(Collision::TRANSPARENT));
    entity.set_interaction(new TriggerInteraction(m_trigger_group, m_on_enter_proc_id_self, m_on_enter_proc_id_other, m_on_exit_proc_id_self));
    globals().access_entity_id = entity.id();
    entity_system().add_accessed_entity(entity.id());
}


