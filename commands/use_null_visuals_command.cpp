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
	try
	{
		globals.entity_system.entity(globals.access_entity_id).set_visuals(new NullVisuals());
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}
