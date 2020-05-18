/*
 * modify_interaction_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_interaction_command.h"
#include "../globals.h"
#include "../math_ext.h"

void ModifyInteractionCommand::execute() const
{
	if(entity_system().entity(globals().access_entity_id))
	{
		Interaction* interaction = entity_system().entity(globals().access_entity_id)->interaction();

		if(is_negative_zero(m_group))
			interaction->clear_groups();
		else
			if(is_negative_zero(m_value))
				interaction->set_group(m_group, false);
			else
				interaction->set_group(m_group, bool(m_value) ^ interaction->is_in_group(m_group));

		if(is_negative_zero(m_trigger_group))
			interaction->set_trigger_group(0);
		else
			interaction->set_trigger_group(interaction->trigger_group() + m_trigger_group);

		if(is_negative_zero(m_proc_id_self))
			interaction->set_proc_id_self(0);
		else
			interaction->set_proc_id_self(interaction->proc_id_self() + m_proc_id_self);

		if(is_negative_zero(m_proc_id_other))
			interaction->set_proc_id_other(0);
		else
			interaction->set_proc_id_other(interaction->proc_id_other() + m_proc_id_other);

		if(is_negative_zero(m_on_exit_proc_id_self))
			interaction->set_on_exit_proc_id_self(0);
		else
			interaction->set_on_exit_proc_id_self(interaction->on_exit_proc_id_self() + m_on_exit_proc_id_self);
	}
	else
	{
		//error globals().access_entity_id
	}
}
