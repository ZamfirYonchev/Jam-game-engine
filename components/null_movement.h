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
	using Base = Movement;
    void print(std::ostream& to) const
    {
    	to << "UseNullMovement ";
    }

    void update(const Time time_diff) {}
    void set_force_x(double val) {}
    void set_force_y(double val) {}
    void mod_force_x(double val) {}
    void mod_force_y(double val) {}
    void set_velocity_x(double val) {}
    void set_velocity_y(double val) {}
    void mod_velocity_x(double val) {}
    void mod_velocity_y(double val) {}
    void set_mass(double val) {}
    void set_friction_x(double val) {}
    void set_friction_y(double val) {}
    void set_move_force(double val) {}
    void set_jump_force(double val) {}
    double fx() const { return 0; }
    double fy() const { return 0; }
    double vx() const { return 0; }
    double vy() const { return 0; }
    double dx() const { return 0; }
    double dy() const { return 0; }
    double mass() const { return 1; }
    double friction_x() const { return 0; }
    double friction_y() const { return 0; }
    double move_force() const { return 0; }
    double jump_force() const { return 0; }
    bool gravity_affected() const { return false; }
    void set_gravity_affected(bool val) {}
    void mod_dx(double dx) {}
    void mod_dy(double dy) {}
};

#endif /* COMPONENTS_NULL_MOVEMENT_H_ */
