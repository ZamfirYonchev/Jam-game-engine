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
    BasicCollision(const bool solid, const double elasticity)
    : m_standing_on(SurfaceType::AIR)
	, m_elasticity(elasticity)
    , m_solid(solid)
    {}

    BasicCollision() : BasicCollision(false, 1) {}

    void print(std::ostream& to) const
    {
    	to << "UseBasicCollision "
    	   << m_solid << " ";
    }

    bool solid() const { return m_solid; }
    void set_solid(const bool val) { m_solid = val; }
    SurfaceType standing_on() const { return m_standing_on; }
    void set_standing_on(SurfaceType surface) { m_standing_on = surface; }
    double on_collision_damage() const { return 0; }
    void set_collision_damage(double) {}
    double elasticity() const { return m_elasticity; }
    void set_elasticity(double val) { m_elasticity = val; }

private:
    SurfaceType m_standing_on;
    double m_elasticity;
    bool m_solid;
};

#endif /* COMPONENTS_BASIC_COLLISION_H_ */
