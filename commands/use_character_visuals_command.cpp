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
	entity_system().entity(globals().access_entity_id)->set_visuals(new CharacterVisuals(m_spr_id));
}
