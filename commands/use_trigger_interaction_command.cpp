/*
 * use_trigger_interaction_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_trigger_interaction_command.h"
#include "../globals.h"
#include "../components/trigger_interaction.h"

void UseTriggerInteractionCommand::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_interaction(new TriggerInteraction(m_trigger_group, m_on_enter_proc_id_self, m_on_enter_proc_id_other, m_on_exit_proc_id_self));
	else
	{
		//error globals().access_entity_id
	}
}
