/*
 * modify_collision_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_collision_command.h"
#include "../math_ext.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

void ModifyCollisionCommand::execute() const
{
	auto& collision = system<EntitySystem>().entity_component<Collision>(system<EntitySystem>().previous_entity_id());
	if(collision)
	{
		if(is_negative_zero(m_state))
			collision.set_state(Collision::CollisionState(0));
		else
			collision.set_state(Collision::CollisionState((int(m_state) + collision.state())%3));

		if(is_negative_zero(m_standing_on))
			collision.set_standing_on(Collision::AIR);
		else
			collision.set_standing_on(Collision::SurfaceType((collision.standing_on()+1)%4));

		if(is_negative_zero(m_on_collision_damage))
			collision.set_collision_damage(0);
		else
			collision.set_collision_damage(collision.on_collision_damage() + m_on_collision_damage);

		if(is_negative_zero(m_elasticity))
			collision.set_elasticity(0);
		else
			collision.set_elasticity(clip(collision.elasticity() + m_elasticity, 0.0, 1.0));
	}
	else
	{
		//error globals.access_entity_id
	}
}
