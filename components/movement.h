/*
 * movement.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_MOVEMENT_H_
#define COMPONENTS_MOVEMENT_H_

#include "../types.h"
#include <sstream>

class Movement
{
public:
    virtual ~Movement() {}
    virtual void print(std::ostream& to) const = 0;

    virtual double fx() const = 0;
    virtual double fy() const = 0;
    virtual double vx() const = 0;
    virtual double vy() const = 0;
    virtual double mass() const = 0;
    virtual double friction() const = 0;
    virtual double move_force() const = 0;
    virtual double jump_force() const = 0;
    virtual bool gravity_affected() const = 0;

    virtual void set_force_x(double val) = 0;
    virtual void set_force_y(double val) = 0;
    virtual void set_velocity_x(double val) = 0;
    virtual void set_velocity_y(double val) = 0;
    virtual void set_mass(double val) = 0;
    virtual void set_friction(double val) = 0;
    virtual void set_move_force(double val) = 0;
    virtual void set_jump_force(double val) = 0;
    virtual void set_gravity_affected(bool val) = 0;

    virtual void mod_force_x(double ax) = 0;
    virtual void mod_force_y(double ay) = 0;
    virtual void mod_velocity_x(double vx) = 0;
    virtual void mod_velocity_y(double vy) = 0;

    static Movement* null;

    friend std::stringstream& operator<< (std::stringstream& out, const Movement& component)
    {
    	component.print(out);
        out << std::endl;
        return out;
    }
};

#endif /* COMPONENTS_MOVEMENT_H_ */
