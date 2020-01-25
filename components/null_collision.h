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
    CollisionState state() const { return TRANSPARENT; }
    void set_state(CollisionState val) {}
    SurfaceType standing_on() const { return GROUND; }
    void set_standing_on(SurfaceType surface) {}
    double on_collision_damage() const { return 0; }
    void set_collision_damage(double) {}
};

#endif /* COMPONENTS_NULL_COLLISION_H_ */
