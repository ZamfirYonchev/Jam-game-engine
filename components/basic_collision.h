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
    BasicCollision(CollisionState state, const double elasticity)
    : m_state(state)
    , m_standing_on(AIR)
	, m_elasticity(elasticity)
	, m_location({})
    {}

    BasicCollision() : BasicCollision(TRANSPARENT, 1) {}

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
    double elasticity() const { return m_elasticity; }
    void set_elasticity(double val) { m_elasticity = val; }

    const RegionLocation& region_location() const { return m_location; }
    void set_region_x(const int val) { m_location.x = val; }
    void set_region_y(const int val) { m_location.y = val; }
    void set_region_x_end(const unsigned int val) { m_location.x_end = val; }
    void set_region_y_end(const unsigned int val) { m_location.y_end = val; }
    void set_region_location(const RegionLocation& val) { m_location = val; }

private:
    CollisionState m_state;
    SurfaceType m_standing_on;
    double m_elasticity;
    RegionLocation m_location;
};

#endif /* COMPONENTS_BASIC_COLLISION_H_ */
