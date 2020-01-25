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
    FullMovement(double max_vx, double max_vy, double move_accel, double jump_accel, bool gravity_affected)
    : m_max_vx(max_vx)
    , m_max_vy(max_vy)
    , m_move_accel(move_accel)
    , m_jump_accel(jump_accel)
    , m_vx(0)
    , m_vy(0)
    , m_ax(0)
    , m_ay(0)
    , m_gravity_affected(gravity_affected)
    {}

    FullMovement(bool gravity_affected) : FullMovement(0, 0, 0, 0, gravity_affected) {}
    FullMovement() : FullMovement(false) {}

    void set_accel_x(double ax) { m_ax = ax; }
    void set_accel_y(double ay) { m_ay = ay; }
    void mod_accel_x(double ax) { m_ax += ax; }
    void mod_accel_y(double ay) { m_ay += ay; }
    void set_velocity_x(double vx) { m_vx = clip(vx, -m_max_vx, m_max_vx); }
    void set_velocity_y(double vy) { m_vy = clip(vy, -m_max_vy, m_max_vy); }
    void mod_velocity_x(double vx) { m_vx = clip(m_vx+vx, -m_max_vx, m_max_vx); }
    void mod_velocity_y(double vy) { m_vy = clip(m_vy+vy, -m_max_vy, m_max_vy); }
    void set_max_vx(double val) { m_max_vx = val; }
    void set_max_vy(double val) { m_max_vy = val; }
    void set_move_accel(double val) { m_move_accel = val; }
    void set_jump_accel(double val) { m_jump_accel = val; }

    double ax() const { return m_ax; }
    double ay() const { return m_ay; }
    double vx() const { return m_vx; }
    double vy() const { return m_vy; }
    double max_vx() const { return m_max_vx; }
    double max_vy() const { return m_max_vy; }
    double move_accel() const { return m_move_accel; }
    double jump_accel() const { return m_jump_accel; }

    bool gravity_affected() const { return m_gravity_affected; }
    void set_gravity_affected(bool val) { m_gravity_affected = val; }

private:
    double m_max_vx, m_max_vy, m_move_accel, m_jump_accel;
    double m_vx, m_vy, m_ax, m_ay;
    bool m_gravity_affected;
};

#endif /* COMPONENTS_FULL_MOVEMENT_H_ */
