/*
 * movement_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_MOVEMENT_SYSTEM_H_
#define SYSTEMS_MOVEMENT_SYSTEM_H_

#include "system_base.h"
#include "../components/position.h"
#include "../components/control.h"
#include "../components/movement.h"
#include "../components/collision.h"
#include "../math_ext.h"
#include <list>
#include <utility>
#include <type_traits>

template<typename EntitySystemT>
class MovementSystem : public SystemBase
{
public:
    constexpr static double GRAVITY_ACCEL = -0.00980665; //always (IRL, 9.80665m/s^2 = 0.00980665mm/ms^2)

    MovementSystem(EntitySystemT& entity_system) : m_entity_system(entity_system) {}

	void update(const Time time_delta, EntitySystemT& entity_system, std::list<std::pair<EntityID, ProcedureID>>& procedure_calls)
    {
    	for(const auto id : entities)
    	{
    		auto& movement = entity_system.entity_component(id, (Movement*)nullptr);
        	if(movement)
        	{
    			const auto& control = entity_system.entity_component(id, (Control*)nullptr);
    			const auto& collision = entity_system.entity_component(id, (Collision*)nullptr);
    			auto& position  = entity_system.entity_component(id, (Position*)nullptr);

    			if(movement.gravity_affected())
    			{
    				movement.mod_force_y(GRAVITY_ACCEL*movement.mass());

    				if(control.decision_jump() && collision.standing_on() == Collision::GROUND)
    					movement.mod_velocity_y(movement.jump_force()/movement.mass());
    			}
    			else
    			{
    				movement.mod_force_y(movement.move_force()*(control.decision_jump() - control.decision_duck()));
    			}

    			movement.mod_force_x(movement.move_force()*control.decision_walk());

    			movement.update(time_delta); //update velocity and displacement

    			position.mod_x(movement.dx());
    			position.mod_y(movement.dy());

    			movement.set_force_x(0);
    			movement.set_force_y(0);
        	}
        	else
        	{
        		//error *it
        	}
    	}
    }

    template<typename T>
    void component_updated(const T& component, const EntityID id, const int8_t change)
    {
    	if constexpr(std::is_same<T, Movement>::value)
		{
    		if(change < 0)
    			remove_id(id);
    		else if(change > 0)
    			add_id(id);
		}
    }

private:
    EntitySystemT& m_entity_system;
};

#endif /* SYSTEMS_MOVEMENT_SYSTEM_H_ */
