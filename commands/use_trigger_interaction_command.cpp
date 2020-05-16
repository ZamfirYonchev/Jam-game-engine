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
	try
	{
		globals.entity_system.entity(globals.access_entity_id).set_interaction(new TriggerInteraction(m_trigger_group, m_on_enter_proc_id_self, m_on_enter_proc_id_other, m_on_exit_proc_id_self));
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}
