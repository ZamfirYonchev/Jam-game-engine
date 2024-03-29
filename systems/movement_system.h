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
#include "../globals.h"
#include <list>
#include <utility>
#include <type_traits>

template<typename EntitySystemT, typename PositionT, typename ControlT, typename MovementT, typename CollisionT>
class MovementSystem : public SystemBase
{
public:
    constexpr static double GRAVITY_ACCEL = -0.00980665; //always (IRL, 9.80665m/s^2 = 0.00980665mm/ms^2)

    MovementSystem(EntitySystemT& entity_system, Globals& _globals)
    : m_entity_system(entity_system)
	, globals{_globals}
    {}

	void update(const Time time_delta)
    {
		if(globals(Globals::app_paused).boolean()) return;

		for(const auto id : entities)
    	{
    		auto& movement = m_entity_system.template entity_component<MovementT>(id);
        	if(movement)
        	{
    			const auto& control = m_entity_system.template entity_component<ControlT>(id);
    			const auto& collision = m_entity_system.template entity_component<CollisionT>(id);
    			auto& position  = m_entity_system.template entity_component<PositionT>(id);

    			if(movement.gravity_affected())
    			{
    				movement.mod_force_y(GRAVITY_ACCEL*movement.mass());

    				if((control.decision_vertical() > 0) && collision.standing_on() == SurfaceType::GROUND)
    					movement.mod_velocity_y(movement.jump_force()/movement.mass());
    			}
    			else
    			{
    				movement.mod_force_y(movement.move_force()*control.decision_vertical());
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
    void component_updated
	( [[maybe_unused]] const T& component
	, [[maybe_unused]] const EntityID id
	, [[maybe_unused]] const int8_t change
	)
    {
    	if constexpr(std::is_same<T, MovementT>::value)
		{
    		if(change < 0)
    			remove_id(id);
    		else if(change > 0)
    			add_id(id);
		}
    }

private:
    EntitySystemT& m_entity_system;
    Globals& globals;
};

#endif /* SYSTEMS_MOVEMENT_SYSTEM_H_ */
