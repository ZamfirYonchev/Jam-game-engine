/*
 * use_null_health_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_null_health_command.h"
#include "../globals.h"
#include "../components/null_health.h"

void UseNullHealthCommand::execute() const
{
	entity_system().entity(globals().access_entity_id)->set_health(new NullHealth());
}
