/*
 * full_interaction.h
 *
 *  Created on: Nov 17, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_FULL_INTERACTION_H_
#define COMPONENTS_FULL_INTERACTION_H_

#include "interaction.h"

class FullInteraction : public Interaction
{
public:
	FullInteraction(int32_t group_vec, int8_t trigger_group, ProcedureID proc_id_self, ProcedureID on_exit_proc_id_self, ProcedureID proc_id_other)
	: m_group_vec(group_vec)
	, m_trigger_group(trigger_group)
	, m_triggered(false)
	, m_proc_id_self(proc_id_self)
	, m_on_exit_proc_id_self(on_exit_proc_id_self)
	, m_proc_id_other(proc_id_other)
	{}

	FullInteraction(int8_t trigger_group, ProcedureID proc_id_self, ProcedureID on_exit_proc_id_self, ProcedureID proc_id_other)
	: FullInteraction(0, trigger_group, proc_id_self, on_exit_proc_id_self, proc_id_other)
	{}

	FullInteraction() : FullInteraction(0, -1, -1, -1) {}

    void print(std::ostream& to) const
    {
    	to << "UseFullInteraction "
    	   << m_group_vec << " "
    	   << int(m_trigger_group) << " "
    	   << m_proc_id_self << " "
    	   << m_proc_id_other << " "
    	   << m_on_exit_proc_id_self << " ";
    }

	bool is_in_group(int group_id) const { return (m_group_vec >> group_id)%2; }
	void set_group(int group_id, bool val)
	{
		int32_t mask = ~(int32_t(1 << group_id));
		m_group_vec = (m_group_vec & mask) | (val << group_id);
	}
	void clear_groups() { m_group_vec = 0; }

	int8_t trigger_group() const { return m_trigger_group; }
	bool triggered() const { return m_triggered; }
	ProcedureID proc_id_self() const { return m_proc_id_self; }
	ProcedureID proc_id_other() const { return m_proc_id_other; }
	ProcedureID on_exit_proc_id_self() const { return m_on_exit_proc_id_self; }

	void set_trigger_group(int8_t group) { m_trigger_group = group; }
	void set_triggered(bool triggered) { m_triggered = triggered; }
	void set_proc_id_self(ProcedureID proc_id) { m_proc_id_self = proc_id; }
	void set_proc_id_other(ProcedureID proc_id) { m_proc_id_other = proc_id; }
	void set_on_exit_proc_id_self(ProcedureID proc_id) { m_on_exit_proc_id_self = proc_id; }

private:
	int32_t m_group_vec;
	int8_t m_trigger_group;
	bool m_triggered;
	ProcedureID m_proc_id_self, m_on_exit_proc_id_self, m_proc_id_other;

};

#endif /* COMPONENTS_FULL_INTERACTION_H_ */
