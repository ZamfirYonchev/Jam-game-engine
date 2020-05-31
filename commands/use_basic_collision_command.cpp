/*
 * use_basic_collision_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_basic_collision_command.h"
#include "../globals.h"
#include "../components/basic_collision.h"

void UseBasicCollisionCommand::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_collision(new BasicCollision(m_state));
	else
	{
		//error globals().access_entity_id
	}
}
