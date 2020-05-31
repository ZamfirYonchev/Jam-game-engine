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
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_position(new NullPosition());
	else
	{
		//error globals().access_entity_id
	}
}
