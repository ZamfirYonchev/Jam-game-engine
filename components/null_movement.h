/*
 * null_movement.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_MOVEMENT_H_
#define COMPONENTS_NULL_MOVEMENT_H_

#include "movement.h"

class NullMovement : public Movement
{
public:
    void set_accel_x(double ax) {}
    void set_accel_y(double ay) {}
    void mod_accel_x(double ax) {}
    void mod_accel_y(double ay) {}
    void set_velocity_x(double vx) {}
    void set_velocity_y(double vy) {}
    void mod_velocity_x(double vx) {}
    void mod_velocity_y(double vy) {}
    void set_max_vx(double vx) {}
    void set_max_vy(double vy) {}
    void set_move_accel(double val) {}
    void set_jump_accel(double val) {}
    double ax() const { return 0; }
    double ay() const { return 0; }
    double vx() const { return 0; }
    double vy() const { return 0; }
    double max_vx() const { return 0; }
    double max_vy() const { return 0; }
    double move_accel() const { return 0; }
    double jump_accel() const { return 0; }
    bool gravity_affected() const { return false; }
    void set_gravity_affected(bool val) {}
};

#endif /* COMPONENTS_NULL_MOVEMENT_H_ */
