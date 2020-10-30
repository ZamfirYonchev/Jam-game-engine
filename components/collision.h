/*
 * collision.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_COLLISION_H_
#define COMPONENTS_COLLISION_H_

#include "../types.h"
#include <ostream>

class NullCollision;

class Collision
{
public:
	using Null = NullCollision;
	struct RegionLocation
	{
		int x, y;
		int x_end, y_end;
		RegionLocation() : x{0}, y{0}, x_end{0}, y_end{0} {}
		RegionLocation(int _x, int _y, int _x_end, int _y_end) : x{_x}, y{_y}, x_end{_x_end}, y_end{_y_end} {}

		bool operator==(const RegionLocation& rhs) const
		{
			return (x==rhs.x) && (y==rhs.y) && (x_end==rhs.x_end) && (y_end==rhs.y_end);
		}

		bool operator!=(const RegionLocation& rhs) const { return !(*this == rhs); }

		bool is_null() const { return (x==x_end) || (y==y_end); }
	};

	enum class SurfaceType {AIR = 0, GROUND = 1};
    enum class CollisionState {TRANSPARENT = 0, MOVEABLE = 1, SOLID = 2};
    virtual ~Collision() {}
    virtual void print(std::ostream& to) const = 0;

    virtual CollisionState state() const = 0;
    virtual SurfaceType standing_on() const = 0;
    virtual double on_collision_damage() const = 0;
    virtual double elasticity() const = 0;

    virtual void set_state(CollisionState val) = 0;
    virtual void set_standing_on(SurfaceType surface) = 0;
    virtual void set_collision_damage(double) = 0;
    virtual void set_elasticity(double val) = 0;

    static Collision* null;

    operator bool() const { return this != null; }

    friend std::ostream& operator<< (std::ostream& out, const Collision& component)
    {
    	component.print(out);
        out << std::endl;
        return out;
    }
};

#endif /* COMPONENTS_COLLISION_H_ */
