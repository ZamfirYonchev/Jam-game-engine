/*
 * damage_collision.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_DAMAGE_COLLISION_H_
#define COMPONENTS_DAMAGE_COLLISION_H_

#include "collision_enums.h"

class DamageCollision
{
public:
    DamageCollision(const bool solid, const double damage)
	: m_damage(damage)
	, m_solid(solid)
	{}
    DamageCollision() : DamageCollision(false, 0) {}

    template<typename ExtractorF>
    DamageCollision
	( ExtractorF&& extract
	)
	: DamageCollision
	  { extract().boolean()
	  , extract().real()
	  }
	{}

    void print(std::ostream& to) const
    {
    	to << "UseDamageCollision "
    	   << m_solid << " "
    	   << m_damage << " ";
    }

    bool solid() const { return m_solid; }
    void set_solid(const bool val) { m_solid = val; }
    SurfaceType standing_on() const { return SurfaceType::AIR; }
    void set_standing_on(SurfaceType) {}
    double on_collision_damage() const { return m_damage; }
    void set_collision_damage(double damage) { m_damage = damage; }
    double elasticity() const { return 1; }
    void set_elasticity(double) {}

private:
    double m_damage;
    bool m_solid;
};

#endif /* COMPONENTS_DAMAGE_COLLISION_H_ */
