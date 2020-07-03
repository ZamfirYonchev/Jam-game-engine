/*
 * normal_interaction.h
 *
 *  Created on: Nov 16, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NORMAL_INTERACTION_H_
#define COMPONENTS_NORMAL_INTERACTION_H_

#include "interaction.h"

class NormalInteraction : public Interaction
{
public:
	using Base = Interaction;
	NormalInteraction(int32_t group_vec)
	: m_group_vec(group_vec)
	{}

	NormalInteraction() : NormalInteraction(0) {}

    void print(std::ostream& to) const
    {
    	to << "UseNormalInteraction "
    	   << m_group_vec << " ";
    }

	bool is_in_group(int group_id) const { return (m_group_vec >> group_id)%2; }
	void set_group(int group_id, bool val)
	{
		int32_t mask = ~(int32_t(1 << group_id));
		m_group_vec = (m_group_vec & mask) | (val << group_id);
	}
	void clear_groups() { m_group_vec = 0; }

	int8_t trigger_group() const { return 0; }
	bool triggered() const { return false; }
	ProcedureID proc_id_self() const { return -1; }
	ProcedureID proc_id_other() const { return -1; }
	ProcedureID on_exit_proc_id_self() const { return -1; }

	void set_trigger_group(int8_t group) {}
	void set_triggered(bool triggered) {}
	void set_proc_id_self(ProcedureID proc_id) {}
	void set_proc_id_other(ProcedureID proc_id) {}
	void set_on_exit_proc_id_self(ProcedureID proc_id) {}

private:
	int32_t m_group_vec;
};

#endif /* COMPONENTS_NORMAL_INTERACTION_H_ */
