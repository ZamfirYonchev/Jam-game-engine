/*
 * use_null_visuals_command.cpp
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#include "use_null_visuals_command.h"
#include "../globals.h"
#include "../components/null_visuals.h"

void UseNullVisualsCommand::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_visuals(new NullVisuals());
	else
	{
		//error globals().access_entity_id
	}
}
