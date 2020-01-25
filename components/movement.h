/*
 * movement.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_MOVEMENT_H_
#define COMPONENTS_MOVEMENT_H_

#include "../types.h"

class Movement
{
public:
    virtual ~Movement() {}

    virtual double ax() const = 0;
    virtual double ay() const = 0;
    virtual double vx() const = 0;
    virtual double vy() const = 0;
    virtual double max_vx() const = 0;
    virtual double max_vy() const = 0;
    virtual double move_accel() const = 0;
    virtual double jump_accel() const = 0;
    virtual bool gravity_affected() const = 0;

    virtual void set_accel_x(double ax) = 0;
    virtual void set_accel_y(double ay) = 0;
    virtual void set_velocity_x(double vx) = 0;
    virtual void set_velocity_y(double vy) = 0;
    virtual void set_max_vx(double vx) = 0;
    virtual void set_max_vy(double vy) = 0;
    virtual void set_move_accel(double val) = 0;
    virtual void set_jump_accel(double val) = 0;
    virtual void set_gravity_affected(bool val) = 0;

    virtual void mod_accel_x(double ax) = 0;
    virtual void mod_accel_y(double ay) = 0;
    virtual void mod_velocity_x(double vx) = 0;
    virtual void mod_velocity_y(double vy) = 0;

    static Movement* null;
};

#endif /* COMPONENTS_MOVEMENT_H_ */
