/*
 * use_normal_interaction_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_normal_interaction_command.h"
#include "../globals.h"
#include "../components/normal_interaction.h"

void UseNormalInteractionCommand::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_interaction(new NormalInteraction(m_group_vec));
	else
	{
		//error globals().access_entity_id
	}
}
