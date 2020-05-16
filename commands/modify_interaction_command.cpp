/*
 * modify_interaction_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_interaction_command.h"
#include "../globals.h"
#include <cmath>

void ModifyInteractionCommand::execute() const
{
	if(m_group == 0 && std::signbit(m_group))
		entity_system().entity(globals().access_entity_id)->interaction()->clear_groups();
	else
		if(m_value == 0 && std::signbit(m_value))
			entity_system().entity(globals().access_entity_id)->interaction()->set_group(m_group, false);
		else
			entity_system().entity(globals().access_entity_id)->interaction()->set_group(m_group, bool(m_value) ^ entity_system().entity(globals().access_entity_id)->interaction()->is_in_group(m_group));

	if(m_trigger_group == 0 && std::signbit(m_trigger_group))
		entity_system().entity(globals().access_entity_id)->interaction()->set_trigger_group(0);
	else
		entity_system().entity(globals().access_entity_id)->interaction()->set_trigger_group(entity_system().entity(globals().access_entity_id)->interaction()->trigger_group() + m_trigger_group);

	if(m_proc_id_self == 0 && std::signbit(m_proc_id_self))
		entity_system().entity(globals().access_entity_id)->interaction()->set_proc_id_self(0);
	else
		entity_system().entity(globals().access_entity_id)->interaction()->set_proc_id_self(entity_system().entity(globals().access_entity_id)->interaction()->proc_id_self() + m_proc_id_self);

	if(m_proc_id_other == 0 && std::signbit(m_proc_id_other))
		entity_system().entity(globals().access_entity_id)->interaction()->set_proc_id_other(0);
	else
		entity_system().entity(globals().access_entity_id)->interaction()->set_proc_id_other(entity_system().entity(globals().access_entity_id)->interaction()->proc_id_other() + m_proc_id_other);

	if(m_on_exit_proc_id_self == 0 && std::signbit(m_on_exit_proc_id_self))
		entity_system().entity(globals().access_entity_id)->interaction()->set_on_exit_proc_id_self(0);
	else
		entity_system().entity(globals().access_entity_id)->interaction()->set_on_exit_proc_id_self(entity_system().entity(globals().access_entity_id)->interaction()->on_exit_proc_id_self() + m_on_exit_proc_id_self);

}
