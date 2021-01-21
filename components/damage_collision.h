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
    DamageCollision(const CollisionState state, const double damage)
	: m_state(state)
	, m_damage(damage)
	{}
    DamageCollision() : DamageCollision(CollisionState::TRANSPARENT, 0) {}

    void print(std::ostream& to) const
    {
    	to << "UseDamageCollision "
    	   << int(m_state) << " "
    	   << m_damage << " ";
    }

    CollisionState state() const { return m_state; }
    void set_state(CollisionState val) { m_state = val; }
    SurfaceType standing_on() const { return SurfaceType::AIR; }
    void set_standing_on(SurfaceType surface) {}
    double on_collision_damage() const { return m_damage; }
    void set_collision_damage(double damage) { m_damage = damage; }
    double elasticity() const { return 1; }
    void set_elasticity(double val) {}

private:
    CollisionState m_state;
    double m_damage;
};

#endif /* COMPONENTS_DAMAGE_COLLISION_H_ */
