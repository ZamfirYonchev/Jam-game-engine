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
	entity_system().entity(globals().access_entity_id)->set_health(new TimedHealth(m_ttl, m_proc_id));
}
