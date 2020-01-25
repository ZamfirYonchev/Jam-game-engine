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
	globals.entity_system.entity(globals.access_entity_id)->set_collision(new BasicCollision(m_state));
}
