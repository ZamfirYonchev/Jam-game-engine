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
	if(entity_system().previous_entity())
	{
		Interaction* interaction = entity_system().previous_entity()->interaction();

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
			interaction->set_proc_id_self(ProcedureID{0});
		else
			interaction->set_proc_id_self(ProcedureID{interaction->proc_id_self() + int(m_proc_id_self)});

		if(is_negative_zero(m_proc_id_other))
			interaction->set_proc_id_other(ProcedureID{0});
		else
			interaction->set_proc_id_other(ProcedureID{interaction->proc_id_other() + int(m_proc_id_other)});

		if(is_negative_zero(m_on_exit_proc_id_self))
			interaction->set_on_exit_proc_id_self(ProcedureID{0});
		else
			interaction->set_on_exit_proc_id_self(ProcedureID{interaction->on_exit_proc_id_self() + int(m_on_exit_proc_id_self)});
	}
	else
	{
		//error globals().access_entity_id
	}
}
