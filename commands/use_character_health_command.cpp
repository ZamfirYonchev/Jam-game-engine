/*
 * use_character_health_command.cpp
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#include "use_character_health_command.h"
#include "../globals.h"
#include "../components/character_health.h"

void UseCharacterHealthCommand::execute() const
{
	if(globals.entity_system.entity(globals.access_entity_id))
		globals.entity_system.entity(globals.access_entity_id)->set_health(new CharacterHealth(m_hp, m_max_hp));
	else
	{
		//error globals.access_entity_id
	}
}
