/*
 * trigger_interaction.h
 *
 *  Created on: Nov 17, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_TRIGGER_INTERACTION_H_
#define COMPONENTS_TRIGGER_INTERACTION_H_

#include "interaction.h"

class TriggerInteraction : public Interaction
{
public:
	using Base = Interaction;
	TriggerInteraction(int8_t trigger_group, ProcedureID proc_id_self, ProcedureID proc_id_other, ProcedureID on_exit_proc_id_self)
	: m_trigger_group(trigger_group)
	, m_proc_id_self(proc_id_self)
	, m_proc_id_other(proc_id_other)
	, m_on_exit_proc_id_self(on_exit_proc_id_self)
	, m_triggered_groups(0)
	, m_last_triggered_groups(0)
	{}

	TriggerInteraction() : TriggerInteraction(0, ProcedureID{-1}, ProcedureID{-1}, ProcedureID{-1}) {}

    void print(std::ostream& to) const
    {
    	to << "UseTriggerInteraction "
    	   << int(m_trigger_group) << " "
    	   << m_proc_id_self << " "
    	   << m_proc_id_other << " "
    	   << m_on_exit_proc_id_self << " ";
    }

	bool is_in_group(int group_id) const { return false; }
	void set_group(int group_id, bool val) {}
	void clear_groups() {}

	int8_t trigger_group() const { return m_trigger_group; }
	ProcedureID proc_id_self() const { return m_proc_id_self; }
	ProcedureID proc_id_other() const { return m_proc_id_other; }
	ProcedureID on_exit_proc_id_self() const { return m_on_exit_proc_id_self; }
	bool triggered() const
	{
		return (m_triggered_groups & (1 << m_trigger_group)) != 0;
	}

	void set_trigger_group(int8_t group) { m_trigger_group = group; }
	void set_proc_id_self(ProcedureID proc_id) { m_proc_id_self = proc_id; }
	void set_proc_id_other(ProcedureID proc_id) { m_proc_id_other = proc_id; }
	void set_on_exit_proc_id_self(ProcedureID proc_id) { m_on_exit_proc_id_self = proc_id; }

	int32_t last_triggered_groups() const { return m_last_triggered_groups; }
	int32_t triggered_groups() const { return m_triggered_groups; }
	void set_triggered_groups(int32_t group_vec) { m_triggered_groups |= group_vec; }
	void update_last_triggered_groups() { m_last_triggered_groups = m_triggered_groups; m_triggered_groups = 0; }
	int32_t group_vector() const { return 0; }

private:
	int8_t m_trigger_group;
	ProcedureID m_proc_id_self, m_proc_id_other, m_on_exit_proc_id_self;
	int32_t m_triggered_groups;
	int32_t m_last_triggered_groups;
};

#endif /* COMPONENTS_TRIGGER_INTERACTION_H_ */
