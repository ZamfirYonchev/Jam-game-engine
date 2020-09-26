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
    DamageCollision(CollisionState state, double damage)
	: m_state(state)
	, m_damage(damage)
	, m_location({})
	{}
    DamageCollision() : DamageCollision(TRANSPARENT, 0) {}

    void print(std::ostream& to) const
    {
    	to << "UseDamageCollision "
    	   << m_state << " "
    	   << m_damage << " ";
    }

    CollisionState state() const { return m_state; }
    void set_state(CollisionState val) { m_state = val; }
    SurfaceType standing_on() const { return AIR; }
    void set_standing_on(SurfaceType surface) {}
    double on_collision_damage() const { return m_damage; }
    void set_collision_damage(double damage) { m_damage = damage; }
    double elasticity() const { return 1; }
    void set_elasticity(double val) {}

    const RegionLocation& region_location() const { return m_location; }
    void set_region_x(int val) { m_location.x = val; }
    void set_region_y(int val) { m_location.y = val; }
    void set_region_x_end(const unsigned int val) { m_location.x_end = val; }
    void set_region_y_end(const unsigned int val) { m_location.y_end = val; }
    void set_region_location(const RegionLocation& val) { m_location = val; }

private:
    CollisionState m_state;
    double m_damage;
    RegionLocation m_location;
};

#endif /* COMPONENTS_DAMAGE_COLLISION_H_ */
