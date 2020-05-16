/*
 * use_health_visuals_command.cpp
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#include "use_health_visuals_command.h"
#include "../globals.h"
#include "../components/character_health_visuals.h"

void UseHealthVisualsCommand::execute() const
{
	try
	{
		globals.entity_system.entity(globals.access_entity_id).set_visuals(new CharacterHealthVisuals(globals.access_entity_id, m_spr_id, m_repeat_x));
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}
