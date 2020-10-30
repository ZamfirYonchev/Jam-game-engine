/*
 * modify_collision_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_COLLISION_COMMAND_H_
#define COMMANDS_MODIFY_COLLISION_COMMAND_H_

#include "../math_ext.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ModifyCollisionCommand
{
public:
	ModifyCollisionCommand(double state, double standing_on, double on_collision_damage, double elasticity)
	: m_state(state)
	, m_standing_on(standing_on)
	, m_on_collision_damage(on_collision_damage)
	, m_elasticity(elasticity)
	{}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	Collision& collision = entity_system.entity_component(entity_system.previous_entity_id(), (Collision*)nullptr);

		if(collision)
		{
			if(is_negative_zero(m_state))
				collision.set_state(Collision::CollisionState(0));
			else
				collision.set_state(Collision::CollisionState((int(m_state) + int(collision.state()))%3));

			if(is_negative_zero(m_standing_on))
				collision.set_standing_on(Collision::SurfaceType::AIR);
			else
				collision.set_standing_on(Collision::SurfaceType((int(collision.standing_on())+1)%4));

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

private:
	double m_state, m_standing_on, m_on_collision_damage, m_elasticity;
};

#endif /* COMMANDS_MODIFY_COLLISION_COMMAND_H_ */
