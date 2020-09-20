/*
 * instant_movement.h
 *
 *  Created on: Dec 7, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_INSTANT_MOVEMENT_H_
#define COMPONENTS_INSTANT_MOVEMENT_H_

#include "movement.h"
#include "../math_ext.h"

class InstantMovement : public Movement
{
public:
	using Base = Movement;
	InstantMovement(double mass, double friction, double move_force)
    : m_mass(mass)
	, m_friction(friction)
	, m_move_force(move_force)
    , m_fx(0)
    , m_fy(0)
	, m_dx(0)
	, m_dy(0)
    {}

    InstantMovement() : InstantMovement(1, 0, 0) {}

    void print(std::ostream& to) const
    {
    	to << "UseInstantMovement "
    	   << m_mass << " "
    	   << m_friction << " "
    	   << m_move_force << " ";
    }

    void update(const Time time_diff)
    {
		const double vx_avg = m_fx*time_diff/m_mass/2.0;
		const double vy_avg = m_fy*time_diff/m_mass/2.0;

		m_fx -= vx_avg * m_friction; //account for air friction
		m_fy -= vy_avg * m_friction; //account for air friction

		m_dx = (m_fx*time_diff/m_mass/2.0)*time_diff;
		m_dy = (m_fy*time_diff/m_mass/2.0)*time_diff;
    }
    void set_force_x(double fx) { m_fx = fx; }
    void set_force_y(double fy) { m_fy = fy; }
    void mod_force_x(double fx) { m_fx += fx; }
    void mod_force_y(double fy) { m_fy += fy; }
    void set_velocity_x(double vx) {}
    void set_velocity_y(double vy) {}
    void mod_velocity_x(double vx) {}
    void mod_velocity_y(double vy) {}
    void set_mass(double val) { m_mass = val; }
    void set_friction(double val) { m_friction = val; }
    void set_move_force(double val) { m_move_force = val; }
    void set_jump_force(double val) {}

    double fx() const { return m_fx; }
    double fy() const { return m_fy; }
    double vx() const { return 0.0; }
    double vy() const { return 0.0; }
    double dx() const { return m_dx; }
    double dy() const { return m_dy; }
    double mass() const { return m_mass; }
    double friction() const { return m_friction; }
    double move_force() const { return m_move_force; }
    double jump_force() const { return 0; }
    void mod_dx(double dx) { m_dx += dx; }
    void mod_dy(double dy) { m_dy += dy; }

    bool gravity_affected() const { return false; }
    void set_gravity_affected(bool val) {}

private:
    double m_mass, m_friction, m_move_force, m_fx, m_fy, m_dx, m_dy;
};




#endif /* COMPONENTS_INSTANT_MOVEMENT_H_ */
