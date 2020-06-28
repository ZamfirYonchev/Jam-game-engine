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
	InstantMovement(double mass, double friction, double move_force)
    : m_mass(mass)
	, m_friction(friction)
	, m_move_force(move_force)
    , m_fx(0)
    , m_fy(0)
    {}

    InstantMovement() : InstantMovement(1, 0, 0) {}

    void print(std::ostream& to) const
    {
    	to << "UseInstantMovement "
    	   << m_mass << " "
    	   << m_friction << " "
    	   << m_move_force << " ";
    }

    void set_force_x(double fx) { m_fx = fx; }
    void set_force_y(double fy) { m_fy = fy; }
    void mod_force_x(double fx) { m_fx += fx; }
    void mod_force_y(double fy) { m_fy += fy; }
    void set_velocity_x(double vx) { set_force_x(vx); }
    void set_velocity_y(double vy) { set_force_y(vy); }
    void mod_velocity_x(double vx) { mod_force_x(vx); }
    void mod_velocity_y(double vy) { mod_force_y(vy); }
    void set_mass(double val) { m_mass = val; }
    void set_friction(double val) { m_friction = val; }
    void set_move_force(double val) { m_move_force = val; }
    void set_jump_force(double val) {}

    double fx() const { return m_fx; }
    double fy() const { return m_fy; }
    double vx() const { return m_fx; }
    double vy() const { return m_fy; }
    double mass() const { return m_mass; }
    double friction() const { return m_friction; }
    double move_force() const { return m_move_force; }
    double jump_force() const { return 0; }

    bool gravity_affected() const { return false; }
    void set_gravity_affected(bool val) {}

private:
    double m_mass, m_friction, m_move_force, m_fx, m_fy;
};




#endif /* COMPONENTS_INSTANT_MOVEMENT_H_ */
