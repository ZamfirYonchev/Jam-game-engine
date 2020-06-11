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
    void set_force_x(double val) {}
    void set_force_y(double val) {}
    void mod_force_x(double val) {}
    void mod_force_y(double val) {}
    void set_velocity_x(double val) {}
    void set_velocity_y(double val) {}
    void mod_velocity_x(double val) {}
    void mod_velocity_y(double val) {}
    void set_mass(double val) {}
    void set_friction(double val) {}
    void set_move_force(double val) {}
    void set_jump_force(double val) {}
    double fx() const { return 0; }
    double fy() const { return 0; }
    double vx() const { return 0; }
    double vy() const { return 0; }
    double mass() const { return 0; }
    double friction() const { return 0; }
    double move_force() const { return 0; }
    double jump_force() const { return 0; }
    bool gravity_affected() const { return false; }
    void set_gravity_affected(bool val) {}
};

#endif /* COMPONENTS_NULL_MOVEMENT_H_ */
