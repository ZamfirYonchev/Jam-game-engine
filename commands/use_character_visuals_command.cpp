/*
 * use_character_visuals_command.cpp
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#include "use_character_visuals_command.h"
#include "../globals.h"
#include "../components/character_visuals.h"

void UseCharacterVisualsCommand::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_visuals(new CharacterVisuals(m_spr_id));
	else
	{
		//error globals().access_entity_id
	}
}
