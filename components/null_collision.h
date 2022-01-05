/*
 * null_collision.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_COLLISION_H_
#define COMPONENTS_NULL_COLLISION_H_

#include "collision_enums.h"

class NullCollision
{
public:

	template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseNullCollision");
    }

    void print(std::ostream& to) const
    {
    	to << "UseNullCollision ";
    }

    bool solid() const { return false; }
    void set_solid(const bool) {}
    SurfaceType standing_on() const { return SurfaceType::GROUND; }
    void set_standing_on(SurfaceType) {}
    double on_collision_damage() const { return 0; }
    void set_collision_damage(double) {}
    double elasticity() const { return 1; }
    void set_elasticity(double) {}
};

#endif /* COMPONENTS_NULL_COLLISION_H_ */
