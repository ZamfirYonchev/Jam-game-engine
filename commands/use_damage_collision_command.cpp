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
	try
	{
		globals.entity_system.entity(globals.access_entity_id).set_collision(new DamageCollision(m_state, m_damage));
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}
