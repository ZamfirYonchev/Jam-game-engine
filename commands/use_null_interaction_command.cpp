/*
 * use_null_interaction_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_null_interaction_command.h"
#include "../globals.h"
#include "../components/null_interaction.h"

void UseNullInteractionCommand::execute() const
{
	try
	{
		globals.entity_system.entity(globals.access_entity_id).set_interaction(new NullInteraction());
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}
