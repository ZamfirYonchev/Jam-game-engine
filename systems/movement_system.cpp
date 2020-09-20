/*
 * movement_system.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "movement_system.h"
#include "../components/movement.h"
#include "../components/control.h"
#include "../components/collision.h"
#include "../globals.h"
#include "../math_ext.h"
#include <algorithm>

void MovementSystem::update(const Time time_delta)
{
	for(const auto id : entities)
	{
    	if(entity_system().entity(id))
    	{
			const Control* control = entity_system().entity(id)->control();
			Movement* movement = entity_system().entity(id)->movement();
			const Collision* collision = entity_system().entity(id)->collision();
			Position* position  = entity_system().entity(id)->position();

			if(movement->gravity_affected())
			{
				movement->mod_force_y(GRAVITY_ACCEL*movement->mass());

				if(control->decision_jump() && collision->standing_on() == Collision::GROUND)
					movement->mod_velocity_y(movement->jump_force()/movement->mass());
			}
			else
			{
				movement->mod_force_y(movement->move_force()*(control->decision_jump() - control->decision_duck()));
			}

			movement->mod_force_x(movement->move_force()*control->decision_walk());

			movement->update(time_delta); //update velocity and displacement

			position->mod_x(movement->dx());
			position->mod_y(movement->dy());

			movement->set_force_x(0);
			movement->set_force_y(0);
    	}
    	else
    	{
    		//error *it
    	}
	}
}


