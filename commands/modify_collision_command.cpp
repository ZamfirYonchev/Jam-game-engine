/*
 * modify_collision_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_collision_command.h"
#include "../globals.h"
#include <cmath>

void ModifyCollisionCommand::execute() const
{
	if(m_state == 0 && std::signbit(m_state))
		entity_system().entity(globals().access_entity_id)->collision()->set_state(Collision::CollisionState(0));
	else
		entity_system().entity(globals().access_entity_id)->collision()->set_state(Collision::CollisionState((int(m_state) + entity_system().entity(globals().access_entity_id)->collision()->state())%3));

	if(m_standing_on == 0 && std::signbit(m_standing_on))
		entity_system().entity(globals().access_entity_id)->collision()->set_standing_on(Collision::AIR);
	else
		entity_system().entity(globals().access_entity_id)->collision()->set_standing_on(Collision::SurfaceType((entity_system().entity(globals().access_entity_id)->collision()->standing_on()+1)%4));

	if(m_on_collision_damage == 0 && std::signbit(m_on_collision_damage))
		entity_system().entity(globals().access_entity_id)->collision()->set_collision_damage(0);
	else
		entity_system().entity(globals().access_entity_id)->collision()->set_collision_damage(entity_system().entity(globals().access_entity_id)->collision()->on_collision_damage() + m_on_collision_damage);

}
