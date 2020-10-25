/*
 * particle_control.h
 *
 *  Created on: Oct 25, 2020
 *      Author: zamfi
 */

#ifndef COMPONENTS_PARTICLE_CONTROL_H_
#define COMPONENTS_PARTICLE_CONTROL_H_
#include "control.h"
#include "../math_ext.h"
#include "position.h"
#include <random>
#include "../math_ext.h"

class ParticleControl : public Control
{
public:
	using Base = Control;
	ParticleControl(std::mt19937& gen, const double random_factor, const double directed_factor, const double direction_angle)
	: m_gen(gen)
	, m_dist(0.0, M_PI*2)
	, m_random_factor(random_factor)
	, m_directed_x(directed_factor*std::cos(direction_angle))
	, m_directed_y(directed_factor*std::sin(direction_angle))
	, m_decision_x(0)
	, m_decision_y(0)
	{}

    void print(std::ostream& to) const
    {
    	to << "UseParticleControl "
    	   << m_random_factor << " "
    	   << std::sqrt(m_directed_x*m_directed_x + m_directed_y*m_directed_y) << " "
    	   << std::atan2(m_directed_y, m_directed_x) << " ";
    }

    double decision_jump() const { return (m_decision_y >= 0.0) * m_decision_y; }
    double decision_duck() const { return (m_decision_y < 0.0) * -1.0 * m_decision_y; }
    bool decision_attack() const { return false; }
    double decision_walk() const { return m_decision_x; }
    ProcedureID attack_proc_id() const { return -1; }
    LookDir look_dir() const { return m_decision_x < 0.0 ? LEFT : RIGHT; }

    void set_decision_jump(double val) {}
    void set_decision_duck(double val) {}
    void set_decision_attack(bool val) {}
    void set_decision_walk(double val) {}
    void set_attack_proc_id(ProcedureID val) {}
    void set_look_dir(LookDir val) {}

    void update_decisions(const Time time_diff)
    {
    	const double angle = m_dist(m_gen);
    	const double vx = m_directed_x + m_random_factor*std::cos(angle);
    	const double vy = m_directed_y + m_random_factor*std::sin(angle);
    	const double v_len = std::sqrt(vx*vx + vy*vy);
       	m_decision_x = v_len != 0 ? vx / v_len : 0.0; //normalize
    	m_decision_y = v_len != 0 ? vy / v_len : 0.0; //normalize
    }

    void clear_decisions()
    {
    	m_decision_x = 0.0;
    	m_decision_y = 0.0;
    }

private:
    std::mt19937& m_gen;
    std::uniform_real_distribution<> m_dist;
    double m_random_factor;
    double m_directed_x, m_directed_y;
    double m_decision_x, m_decision_y;
};

#endif /* COMPONENTS_PARTICLE_CONTROL_H_ */
