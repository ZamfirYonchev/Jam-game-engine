/*
 * use_null_control_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_null_control_command.h"
#include "../globals.h"
#include "../components/null_control.h"

void UseNullControlCommand::execute() const
{
	if(entity_system().entity(globals().access_entity_id))
		entity_system().entity(globals().access_entity_id)->set_control(new NullControl());
	else
	{
		//error globals().access_entity_id
	}
}
