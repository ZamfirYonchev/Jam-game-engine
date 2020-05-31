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
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_collision(new DamageCollision(m_state, m_damage));
	else
	{
		//error globals().access_entity_id
	}
}
