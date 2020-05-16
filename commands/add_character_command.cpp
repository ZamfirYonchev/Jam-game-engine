/*
 * add_character_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_character_command.h"
#include "../globals.h"
#include "../entity.h"
#include "../components/absolute_position.h"
#include "../components/full_movement.h"
#include "../components/basic_collision.h"
#include "../components/normal_interaction.h"
#include "../components/character_health.h"
#include "../components/character_visuals.h"

void AddCharacterCommand::execute() const
{
    globals.entity_system.add_new_entity();
    try
    {
    	Entity& entity = globals.entity_system.entity(globals.entity_system.last_id());
		entity.set_position(new AbsolutePosition(m_x, m_y, m_w, m_h));
		entity.set_movement(new FullMovement(0.5, 2, 0.012, 1.5, true));
		entity.set_collision(new BasicCollision(Collision::MOVEABLE));
		entity.set_interaction(new NormalInteraction());
		entity.set_health(new CharacterHealth(m_hp));
		entity.set_visuals(new CharacterVisuals(m_spr_id));
		globals.access_entity_id = globals.entity_system.last_id();
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}
