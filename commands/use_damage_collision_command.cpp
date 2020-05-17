/*
 * use_damage_collision_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_damage_collision_command.h"
#include "../globals.h"
#include "../components/damage_collision.h"

void UseDamageCollisionCommand::execute() const
{
	if(entity_system().entity(globals().access_entity_id))
		entity_system().entity(globals().access_entity_id)->set_collision(new DamageCollision(m_state, m_damage));
	else
	{
		//error globals().access_entity_id
	}
}
