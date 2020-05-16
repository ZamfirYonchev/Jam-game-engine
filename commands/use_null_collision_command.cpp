/*
 * use_null_collision_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_null_collision_command.h"
#include "../globals.h"
#include "../components/null_collision.h"

void UseNullCollisionCommand::execute() const
{
	entity_system().entity(globals().access_entity_id)->set_collision(new NullCollision());
}
