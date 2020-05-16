/*
 * use_null_movement_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_null_movement_command.h"
#include "../globals.h"
#include "../components/null_movement.h"

void UseNullMovementCommand::execute() const
{
	try
	{
		globals.entity_system.entity(globals.access_entity_id).set_movement(new NullMovement());
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}
