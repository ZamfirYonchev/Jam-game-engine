/*
 * basic_collision.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_BASIC_COLLISION_H_
#define COMPONENTS_BASIC_COLLISION_H_

#include "collision.h"

class BasicCollision : public Collision
{
public:
	using Base = Collision;
    BasicCollision(CollisionState state)
    : m_state(state)
    , m_standing_on(AIR)
    {}

    BasicCollision() : BasicCollision(TRANSPARENT) {}

    void print(std::ostream& to) const
    {
    	to << "UseBasicCollision "
    	   << m_state << " ";
    }

    CollisionState state() const { return m_state; }
    void set_state(CollisionState val) { m_state = val; }
    SurfaceType standing_on() const { return m_standing_on; }
    void set_standing_on(SurfaceType surface) { m_standing_on = surface; }
    double on_collision_damage() const { return 0; }
    void set_collision_damage(double) {}

private:
    CollisionState m_state;
    SurfaceType m_standing_on;
};

#endif /* COMPONENTS_BASIC_COLLISION_H_ */
