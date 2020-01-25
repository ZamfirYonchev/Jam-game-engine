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
	InstantMovement(double move_accel)
    : m_move_accel(move_accel)
    , m_ax(0)
    , m_ay(0)
    {}

    InstantMovement() : InstantMovement(0) {}

    void set_accel_x(double ax) { m_ax = clip(ax, -m_move_accel, m_move_accel); }
    void set_accel_y(double ay) { m_ay = clip(ay, -m_move_accel, m_move_accel); }
    void mod_accel_x(double ax) { m_ax = clip(m_ax + ax, -m_move_accel, m_move_accel); }
    void mod_accel_y(double ay) { m_ay += clip(m_ay + ay, -m_move_accel, m_move_accel); }
    void set_velocity_x(double vx) { set_accel_x(vx); }
    void set_velocity_y(double vy) { set_accel_y(vy); }
    void mod_velocity_x(double vx) { set_accel_x(m_ax+vx); }
    void mod_velocity_y(double vy) { set_accel_y(m_ay+vy); }
    void set_max_vx(double val) {}
    void set_max_vy(double val) {}
    void set_move_accel(double val) { m_move_accel = val; }
    void set_jump_accel(double val) {}

    double ax() const { return m_ax; }
    double ay() const { return m_ay; }
    double vx() const { return m_ax; }
    double vy() const { return m_ay; }
    double max_vx() const { return m_ax; }
    double max_vy() const { return m_ay; }
    double move_accel() const { return m_move_accel; }
    double jump_accel() const { return 0; }

    bool gravity_affected() const { return false; }
    void set_gravity_affected(bool val) {}

private:
    double m_move_accel, m_ax, m_ay;
};




#endif /* COMPONENTS_INSTANT_MOVEMENT_H_ */
