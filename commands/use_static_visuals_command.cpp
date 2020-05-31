/*
 * use_static_visuals_command.cpp
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#include "use_static_visuals_command.h"
#include "../globals.h"
#include "../components/static_visuals.h"

void UseStaticVisualsCommand::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_visuals(new StaticVisuals(m_spr_id, m_sprite));
	else
	{
		//error globals().access_entity_id
	}
}
