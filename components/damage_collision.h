/*
 * damage_collision.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_DAMAGE_COLLISION_H_
#define COMPONENTS_DAMAGE_COLLISION_H_

#include "collision.h"

class DamageCollision : public Collision
{
public:
	using Base = Collision;
    DamageCollision(const bool solid, const double damage)
	: m_damage(damage)
	, m_solid(solid)
	{}
    DamageCollision() : DamageCollision(false, 0) {}

    void print(std::ostream& to) const
    {
    	to << "UseDamageCollision "
    	   << m_solid << " "
    	   << m_damage << " ";
    }

    bool solid() const { return m_solid; }
    void set_solid(const bool val) { m_solid = val; }
    SurfaceType standing_on() const { return SurfaceType::AIR; }
    void set_standing_on(SurfaceType surface) {}
    double on_collision_damage() const { return m_damage; }
    void set_collision_damage(double damage) { m_damage = damage; }
    double elasticity() const { return 1; }
    void set_elasticity(double val) {}

private:
    double m_damage;
    bool m_solid;
};

#endif /* COMPONENTS_DAMAGE_COLLISION_H_ */
