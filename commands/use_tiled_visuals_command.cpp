/*
 * use_tiled_visuals_command.cpp
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#include "use_tiled_visuals_command.h"
#include "../globals.h"
#include "../components/tiled_visuals.h"

void UseTiledVisualsCommand::execute() const
{
	try
	{
		globals.entity_system.entity(globals.access_entity_id).set_visuals(new TiledVisuals(m_spr_id, m_repeat_x, m_repeat_y));
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}
