/*
 * use_null_position_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_null_position_command.h"
#include "../globals.h"
#include "../components/null_position.h"

void UseNullPositionCommand::execute() const
{
	if(entity_system().entity(globals().access_entity_id))
		entity_system().entity(globals().access_entity_id)->set_position(new NullPosition());
	else
	{
		//error globals().access_entity_id
	}
}
