/*
 * null_movement.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_MOVEMENT_H_
#define COMPONENTS_NULL_MOVEMENT_H_

class NullMovement
{
public:
	template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseNullMovement");
    }

    void print(std::ostream& to) const
    {
    	to << "UseNullMovement ";
    }

    void update(const Time) {}
    void set_force_x(double) {}
    void set_force_y(double) {}
    void mod_force_x(double) {}
    void mod_force_y(double) {}
    void set_velocity_x(double) {}
    void set_velocity_y(double) {}
    void mod_velocity_x(double) {}
    void mod_velocity_y(double) {}
    void set_mass(double) {}
    void set_friction_x(double) {}
    void set_friction_y(double) {}
    void set_move_force(double) {}
    void set_jump_force(double) {}
    double fx() const { return 0; }
    double fy() const { return 0; }
    double vx() const { return 0; }
    double vy() const { return 0; }
    double dx() const { return 0; }
    double dy() const { return 0; }
    double mass() const { return std::numeric_limits<double>::max(); }
    double friction_x() const { return 0; }
    double friction_y() const { return 0; }
    double move_force() const { return 0; }
    double jump_force() const { return 0; }
    bool gravity_affected() const { return false; }
    void set_gravity_affected(bool) {}
    void mod_dx(double) {}
    void mod_dy(double) {}
    std::pair<double, double> displacement(const Time) const { return {0.0, 0.0}; }
};

#endif /* COMPONENTS_NULL_MOVEMENT_H_ */
