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
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_interaction(new NullInteraction());
	else
	{
		//error globals().access_entity_id
	}
}
