/*
 * particle_control.h
 *
 *  Created on: Oct 25, 2020
 *      Author: zamfi
 */

#ifndef COMPONENTS_PARTICLE_CONTROL_H_
#define COMPONENTS_PARTICLE_CONTROL_H_

#include "control_enums.h"
#include "../math_ext.h"
#include <random>

class ParticleControl
{
public:
	ParticleControl
	( std::mt19937& gen
	, const double random_factor
	, const double directed_factor
	, const double direction_angle
	)
	: m_gen(gen)
	, m_dist(0.0, M_PI*2)
	, m_random_factor(random_factor)
	, m_directed_x(directed_factor*std::cos(direction_angle))
	, m_directed_y(directed_factor*std::sin(direction_angle))
	, m_decision_x(0)
	, m_decision_y(0)
	, m_offset_x(0)
	, m_offset_y(0)
	{}

    template<typename ExtractorF>
	ParticleControl
	( ExtractorF&& extract
	, std::mt19937& gen
	)
	: ParticleControl
	  { gen
	  , extract().real()
	  , extract().real()
	  , extract().real()
	  }
	{}

	template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseParticleControl");
    	insert(m_random_factor);
    	insert(std::sqrt(m_directed_x*m_directed_x + m_directed_y*m_directed_y));
    	insert(std::atan2(m_directed_y, m_directed_x));
    }

    void print(std::ostream& to) const
    {
    	to << "UseParticleControl "
    	   << m_random_factor << " "
    	   << std::sqrt(m_directed_x*m_directed_x + m_directed_y*m_directed_y) << " "
    	   << std::atan2(m_directed_y, m_directed_x) << " ";
    }

    double decision_vertical() const { return m_decision_y; }
    bool decision_attack() const { return false; }
    double decision_walk() const { return m_decision_x; }
    ProcedureID attack_proc_id() const { return ProcedureID{0}; }
    LookDir look_dir() const { return m_decision_x < 0.0 ? LookDir::LEFT : LookDir::RIGHT; }

    void set_decision_vertical(double val) { m_offset_y = clip(val, -1.0, 1.0); }
    void set_decision_attack(bool) {}
    void set_decision_walk(double val) { m_offset_x = clip(val, -1.0, 1.0); }
    void mod_decision_vertical(double val) { m_offset_y = val; }
    void mod_decision_walk(double val) { m_offset_x = val; }
    void set_attack_proc_id(ProcedureID) {}
    void set_look_dir(LookDir) {}

    void update_decisions(const Time time_diff)
    {
    	const double angle = m_dist(m_gen.get());
    	const double vx = m_offset_x + m_directed_x + m_random_factor*std::cos(angle);
    	const double vy = m_offset_y + m_directed_y + m_random_factor*std::sin(angle);
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
    std::reference_wrapper<std::mt19937> m_gen;
    std::uniform_real_distribution<> m_dist;
    double m_random_factor;
    double m_directed_x, m_directed_y;
    double m_decision_x, m_decision_y;
    double m_offset_x, m_offset_y;
};

#endif /* COMPONENTS_PARTICLE_CONTROL_H_ */
