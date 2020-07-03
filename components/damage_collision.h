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

private:
    CollisionState m_state;
    double m_damage;
};

#endif /* COMPONENTS_DAMAGE_COLLISION_H_ */
