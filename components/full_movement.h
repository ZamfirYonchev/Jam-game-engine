/*
 * full_movement.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_FULL_MOVEMENT_H_
#define COMPONENTS_FULL_MOVEMENT_H_

#include "movement.h"
#include "../math_ext.h"

class FullMovement : public Movement
{
public:
	using Base = Movement;
    FullMovement(double mass, double friction, double move_force, double jump_force, bool gravity_affected)
    : m_mass(mass)
    , m_friction(friction)
    , m_move_force(move_force)
    , m_jump_force(jump_force)
    , m_vx(0)
    , m_vy(0)
    , m_fx(0)
    , m_fy(0)
    , m_dx(0)
    , m_dy(0)
    , m_gravity_affected(gravity_affected)
    {}

    FullMovement(bool gravity_affected) : FullMovement(0, 0, 0, 0, gravity_affected) {}
    FullMovement() : FullMovement(false) {}

    void print(std::ostream& to) const
    {
    	to << "UseFullMovement "
    	   << m_mass << " "
    	   << m_friction << " "
    	   << m_move_force << " "
    	   << m_jump_force << " "
    	   << m_gravity_affected << " ";
    }

    void update(const Time time_diff)
    {
		const double vx_avg = m_vx + m_fx*time_diff/m_mass/2.0;
		const double vy_avg = m_vy + m_fy*time_diff/m_mass/2.0;

		m_fx -= vx_avg * m_friction; //account for air friction
		m_fy -= vy_avg * m_friction; //account for air friction

		m_dx = (m_vx + m_fx*time_diff/m_mass/2.0)*time_diff;
		m_dy = (m_vy + m_fy*time_diff/m_mass/2.0)*time_diff;


		m_vx += m_fx * time_diff / m_mass;
		m_vy += m_fy * time_diff / m_mass;

		if(sign(m_dx) != sign(vx_avg))
		{
			m_dx = 0;
			m_vx = 0;
		}

		if(sign(m_dy) != sign(vy_avg))
		{
			m_dy = 0;
			m_vy = 0;
		}
    }

    void set_force_x(double fx) { m_fx = fx; }
    void set_force_y(double fy) { m_fy = fy; }
    void mod_force_x(double fx) { m_fx += fx; }
    void mod_force_y(double fy) { m_fy += fy; }
    void set_velocity_x(double vx) { m_vx = vx; }
    void set_velocity_y(double vy) { m_vy = vy; }
    void mod_velocity_x(double vx) { m_vx = m_vx+vx; }
    void mod_velocity_y(double vy) { m_vy = m_vy+vy; }
    void set_mass(double val) { m_mass = val; }
    void set_friction(double val) { m_friction = val; }
    void set_move_force(double val) { m_move_force = val; }
    void set_jump_force(double val) { m_jump_force = val; }
    void mod_dx(double dx) { m_dx += dx; }
    void mod_dy(double dy) { m_dy += dy; }

    double fx() const { return m_fx; }
    double fy() const { return m_fy; }
    double vx() const { return m_vx; }
    double vy() const { return m_vy; }
    double dx() const { return m_dx; }
    double dy() const { return m_dy; }
    double mass() const { return m_mass; }
    double friction() const { return m_friction; }
    double move_force() const { return m_move_force; }
    double jump_force() const { return m_jump_force; }

    bool gravity_affected() const { return m_gravity_affected; }
    void set_gravity_affected(bool val) { m_gravity_affected = val; }

private:
    double m_mass, m_friction, m_move_force, m_jump_force;
    double m_vx, m_vy, m_fx, m_fy, m_dx, m_dy;
    bool m_gravity_affected;
};

#endif /* COMPONENTS_FULL_MOVEMENT_H_ */
