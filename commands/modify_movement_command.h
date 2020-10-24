/*
 * modify_movement_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_MOVEMENT_COMMAND_H_
#define COMMANDS_MODIFY_MOVEMENT_COMMAND_H_

#include "../math_ext.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ModifyMovementCommand
{
public:
	ModifyMovementCommand(double mass, double friction, double vx, double vy, double fx, double fy, double gravity_affected)
	: m_mass(mass)
	, m_friction(friction)
	, m_vx(vx)
	, m_vy(vy)
	, m_fx(fx)
	, m_fy(fy)
	, m_gravity_affected(gravity_affected)
	{}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	Movement& movement = entity_system.entity_component(entity_system.previous_entity_id(), (Movement*)nullptr);

		if(movement)
		{
			if(is_negative_zero(m_mass))
				movement.set_mass(m_mass);
			else
				movement.set_mass(movement.mass() + m_mass);

			if(is_negative_zero(m_friction))
				movement.set_friction(m_friction);
			else
				movement.set_friction(movement.friction() + m_friction);

			if(is_negative_zero(m_fx))
				movement.set_force_x(m_fx);
			else
				movement.mod_force_x(m_fx);

			if(is_negative_zero(m_fy))
				movement.set_force_y(m_fy);
			else
				movement.mod_force_y(m_fy);

			if(is_negative_zero(m_vx))
				movement.set_velocity_x(m_vx);
			else
				movement.mod_velocity_x(m_vx);

			if(is_negative_zero(m_vy))
				movement.set_velocity_y(m_vy);
			else
				movement.mod_velocity_y(m_vy);

			if(is_negative_zero(m_gravity_affected))
				movement.set_gravity_affected(bool(m_gravity_affected));
			else
				movement.set_gravity_affected(bool(m_gravity_affected) ^ movement.gravity_affected());
		}
		else
		{
			//error entity_system.previous_entity_id()
		}
	}

private:
    double m_mass, m_friction, m_vx, m_vy, m_fx, m_fy, m_gravity_affected;
};


#endif /* COMMANDS_MODIFY_MOVEMENT_COMMAND_H_ */
