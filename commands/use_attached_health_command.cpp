/*
 * use_attached_health_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_attached_health_command.h"
#include "../globals.h"
#include "../components/attached_health.h"

void UseAttachedHealthCommand::execute() const
{
	try
	{
		globals.entity_system.entity(globals.access_entity_id).set_health(new AttachedHealth(m_attached_id, m_offset_hp, m_offset_max_hp));
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}
