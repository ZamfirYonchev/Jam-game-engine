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

void MovementSystem::update(Time time_delta)
{
    for(auto it = entities.begin(); it != entities.end(); ++it)
    {
    	try
    	{
			Control* control = globals.entity_system.entity(*it).control();
			Movement* movement = globals.entity_system.entity(*it).movement();
			Collision* collision = globals.entity_system.entity(*it).collision();

			if(movement->gravity_affected())
			{
				movement->mod_accel_y(GRAVITY_ACCEL);

				if(control->decision_jump() && collision->standing_on() == Collision::GROUND)
					movement->mod_velocity_y(movement->jump_accel());
			}
			else
			{
				if(control->decision_jump())
					movement->mod_accel_y(movement->move_accel());
				if(control->decision_duck())
					movement->mod_accel_y(-movement->move_accel());
			}


			movement->mod_accel_x(movement->move_accel()*control->decision_walk());

			double sx = clip((movement->vx() + movement->ax()*time_delta/2.0)*time_delta, -movement->max_vx()*time_delta, movement->max_vx()*time_delta);
			double sy = clip((movement->vy() + movement->ay()*time_delta/2.0)*time_delta, -movement->max_vy()*time_delta, movement->max_vy()*time_delta);

			//std::cout << "vx = " << movement->vx() << " ax = "<< movement->ax() << " time = " << time_delta << " sx " << sx << std::endl;
			globals.entity_system.entity(*it).position()->mod_x(sx);
			globals.entity_system.entity(*it).position()->mod_y(sy);

			movement->mod_velocity_x(movement->ax()*time_delta);
			movement->mod_velocity_y(movement->ay()*time_delta);
			movement->mod_velocity_x(-0.1*movement->vx()); //air friction
			movement->mod_velocity_y(-0.1*movement->vy()); //air friction

			movement->set_accel_x(0);
			movement->set_accel_y(0);
    	}
    	catch(std::out_of_range& except)
    	{
    		//error message
    	}
    }
}


