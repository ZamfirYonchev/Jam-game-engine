/*
 * timed_control.h
 *
 *  Created on: Jan 27, 2021
 *      Author: zamfi
 */

#ifndef COMPONENTS_TIMED_CONTROL_H_
#define COMPONENTS_TIMED_CONTROL_H_

#include "control.h"
#include "../math_ext.h"
#include "../commands/use_component_command.h"

class TimedControl : public Control
{
public:
	using Base = Control;
	TimedControl
		(const Time max_duration
	   , const int repeats
	   , const ProcedureID proc_id
		)
	: m_max_duration{max_duration}
	, m_current_duration{0}
	, m_proc_id{proc_id}
	, m_attack{false}
	, m_repeats{repeats}
	, m_walk{1}
	{}

    void print(std::ostream& to) const
    {
    	to << "UseTimedControl "
    	   << m_max_duration << " "
    	   << m_repeats << " ";
    }

    double decision_vertical() const { return 0; }
    bool decision_attack() const { return m_attack; }
    double decision_walk() const { return m_walk; }
    ProcedureID attack_proc_id() const { return m_proc_id; }
    LookDir look_dir() const { return m_walk < 0 ? Control::LookDir::LEFT : Control::LookDir::RIGHT; }

    void set_decision_vertical(double val) {}
    void set_decision_attack(bool val) {}
    void set_decision_walk(double val) {}
    void mod_decision_vertical(double val) {}
    void mod_decision_walk(double val) {}
    void set_attack_proc_id(ProcedureID val) { m_proc_id = val; }
    void set_look_dir(LookDir val) {}

    void update_decisions(const Time time_diff)
    {
		m_current_duration += time_diff*(m_repeats != 0);
		m_repeats -= (m_repeats > 0)*(m_current_duration >= m_max_duration);
		m_walk *= (1 - 2*(m_current_duration >= m_max_duration))*(m_repeats != 0);
		m_attack = m_current_duration >= m_max_duration;
		m_current_duration *= (m_current_duration < m_max_duration);
    }

    void clear_decisions()
    {
        m_walk = 0;
        m_attack = false;
    }

private:
    Time m_max_duration;
    Time m_current_duration;
    ProcedureID m_proc_id;
    bool m_attack;
    int m_repeats;
    int8_t m_walk;
};

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<TimedControl>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto max_duration = command_system.exec_next();
	const auto repeats = command_system.exec_next();
	const auto proc_id = command_system.exec_next();

	set_component(entity_system, rendering_system, all_systems, globals, {max_duration.integer(), repeats.integer(), proc_id.integer()});

	return CommandReturnValue{0.0};
}

#endif /* COMPONENTS_TIMED_CONTROL_H_ */
