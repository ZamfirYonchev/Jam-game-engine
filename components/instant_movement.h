/*
 * instant_movement.h
 *
 *  Created on: Dec 7, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_INSTANT_MOVEMENT_H_
#define COMPONENTS_INSTANT_MOVEMENT_H_

#include "../math_ext.h"

class InstantMovement
{
public:
	InstantMovement
		(const double mass
	   , const double friction_x
	   , const double friction_y
	   , const double move_force)
    : m_mass(mass)
	, m_friction_x(friction_x)
	, m_friction_y(friction_y)
	, m_move_force(move_force)
    , m_fx(0)
    , m_fy(0)
	, m_dx(0)
	, m_dy(0)
    {}

    template<typename ExtractorF>
	InstantMovement
	( ExtractorF&& extract
	)
	: InstantMovement
	  { extract().real()
	  , extract().real()
	  , extract().real()
	  , extract().real()
	  }
    {}

    InstantMovement() : InstantMovement(1, 0, 0, 0) {}

    void print(std::ostream& to) const
    {
    	to << "UseInstantMovement "
    	   << m_mass << " "
    	   << m_friction_x << " "
    	   << m_friction_y << " "
    	   << m_move_force << " ";
    }

    void update(const Time time_diff)
    {
		const double vx_avg = m_fx*time_diff/m_mass/2.0;
		const double vy_avg = m_fy*time_diff/m_mass/2.0;

		const double fx = m_fx - vx_avg * m_friction_x;
		const double fy = m_fy - vy_avg * m_friction_y;

		m_dx = (fx*time_diff/m_mass/2.0)*time_diff;
		m_dy = (fy*time_diff/m_mass/2.0)*time_diff;
    }

    std::pair<double, double> displacement(const Time time_diff) const
	{
		const double vx_avg = m_fx*time_diff/m_mass/2.0;
		const double vy_avg = m_fy*time_diff/m_mass/2.0;

		//account for air friction
		const double fx = m_fx - vx_avg * m_friction_x;
		const double fy = m_fy - vy_avg * m_friction_y;

		const double dx = (fx*time_diff/m_mass/2.0)*time_diff;
		const double dy = (fy*time_diff/m_mass/2.0)*time_diff;

		return {dx, dy};
	}

    void set_force_x(double fx) { m_fx = fx; }
    void set_force_y(double fy) { m_fy = fy; }
    void mod_force_x(double fx) { m_fx += fx; }
    void mod_force_y(double fy) { m_fy += fy; }
    void set_velocity_x(double) {}
    void set_velocity_y(double) {}
    void mod_velocity_x(double) {}
    void mod_velocity_y(double) {}
    void set_mass(double val) { m_mass = val; }
    void set_friction_x(double val) { m_friction_x = val; }
    void set_friction_y(double val) { m_friction_y = val; }
    void set_move_force(double val) { m_move_force = val; }
    void set_jump_force(double) {}

    double fx() const { return m_fx; }
    double fy() const { return m_fy; }
    double vx() const { return 0.0; }
    double vy() const { return 0.0; }
    double dx() const { return m_dx; }
    double dy() const { return m_dy; }
    double mass() const { return m_mass; }
    double friction_x() const { return m_friction_x; }
    double friction_y() const { return m_friction_y; }
    double move_force() const { return m_move_force; }
    double jump_force() const { return 0; }
    void mod_dx(double dx) { m_dx += dx; }
    void mod_dy(double dy) { m_dy += dy; }

    bool gravity_affected() const { return false; }
    void set_gravity_affected(bool) {}

private:
    double m_mass, m_friction_x, m_friction_y, m_move_force, m_fx, m_fy, m_dx, m_dy;
};




#endif /* COMPONENTS_INSTANT_MOVEMENT_H_ */
