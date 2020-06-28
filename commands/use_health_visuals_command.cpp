/*
 * use_health_visuals_command.cpp
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#include "use_health_visuals_command.h"

#include "../components/health_visuals.h"
#include "../globals.h"

void UseHealthVisualsCommand::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_visuals(new HealthVisuals(entity_system().previous_entity()->id(), m_spr_id, m_repeat_x));
	else
	{
		//error globals().access_entity_id
	}
}
