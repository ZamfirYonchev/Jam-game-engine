/*
 * null_collision.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_COLLISION_H_
#define COMPONENTS_NULL_COLLISION_H_

#include "collision.h"

class NullCollision : public Collision
{
public:
	using Base = Collision;
    void print(std::ostream& to) const
    {
    	to << "UseNullCollision ";
    }

    CollisionState state() const { return TRANSPARENT; }
    void set_state(CollisionState val) {}
    SurfaceType standing_on() const { return GROUND; }
    void set_standing_on(SurfaceType surface) {}
    double on_collision_damage() const { return 0; }
    void set_collision_damage(double) {}
    double elasticity() const { return 1; }
    void set_elasticity(double val) {}

    const RegionLocation& region_location() const { return null_location; }
    void set_region_x(int val) {}
    void set_region_y(int val) {}
    void set_region_x_end(const unsigned int val) {}
    void set_region_y_end(const unsigned int val) {}
    void set_region_location(const RegionLocation& val) {}

private:
    static const RegionLocation null_location;
};

#endif /* COMPONENTS_NULL_COLLISION_H_ */
