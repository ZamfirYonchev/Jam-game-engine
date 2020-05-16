/*
 * use_timed_health_command.cpp
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#include "use_timed_health_command.h"
#include "../globals.h"
#include "../components/timed_health.h"

void UseTimedHealthCommand::execute() const
{
	try
	{
		globals.entity_system.entity(globals.access_entity_id).set_health(new TimedHealth(m_ttl, m_proc_id));
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}
