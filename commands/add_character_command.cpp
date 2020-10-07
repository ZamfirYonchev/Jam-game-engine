/*
 * add_character_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_character_command.h"
#include "../entity.h"
#include "../components/absolute_position.h"
#include "../components/full_movement.h"
#include "../components/basic_collision.h"
#include "../components/normal_interaction.h"
#include "../components/character_health.h"
#include "../components/character_visuals.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

void AddCharacterCommand::execute() const
{
	Entity& entity = system<EntitySystem>().add_new_entity();
    entity.set_component<AbsolutePosition>(m_x, m_y, m_w, m_h);
    entity.set_component<FullMovement>(0.5, 2.0, 0.012, 1.5, true);
    entity.set_component<BasicCollision>(Collision::MOVEABLE, 1.0);
    entity.set_component<NormalInteraction>();
    entity.set_component<CharacterHealth>(m_hp);
    entity.set_component<CharacterVisuals>(m_spr_id);
    system<EntitySystem>().add_accessed_entity(entity.id());
}
