/*
 * use_full_interaction_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_full_interaction_command.h"
#include "../globals.h"
#include "../components/full_interaction.h"

void UseFullInteractionCommand::execute() const
{
	if(entity_system().entity(globals().access_entity_id))
		entity_system().entity(globals().access_entity_id)->set_interaction(new FullInteraction(m_group_vec, m_trigger_group, m_on_enter_proc_id_self, m_on_enter_proc_id_other, m_on_exit_proc_id_self));
	else
	{
		//error globals().access_entity_id
	}
}
