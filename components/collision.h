/*
 * collision.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_COLLISION_H_
#define COMPONENTS_COLLISION_H_

#include "../types.h"
#include <sstream>

class Collision
{
public:
    enum SurfaceType {AIR = 0, GROUND = 1};
    enum CollisionState {TRANSPARENT = 0, MOVEABLE = 1, SOLID = 2};
    virtual ~Collision() {}
    virtual void print(std::ostream& to) const = 0;

    virtual CollisionState state() const = 0;
    virtual SurfaceType standing_on() const = 0;
    virtual double on_collision_damage() const = 0;

    virtual void set_state(CollisionState val) = 0;
    virtual void set_standing_on(SurfaceType surface) = 0;
    virtual void set_collision_damage(double) = 0;

    static Collision* null;

    friend std::stringstream& operator<< (std::stringstream& out, const Collision& component)
    {
    	component.print(out);
        out << std::endl;
        return out;
    }
};

#endif /* COMPONENTS_COLLISION_H_ */
