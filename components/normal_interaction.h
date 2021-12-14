/*
 * normal_interaction.h
 *
 *  Created on: Nov 16, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NORMAL_INTERACTION_H_
#define COMPONENTS_NORMAL_INTERACTION_H_

#include <cinttypes>

class NormalInteraction
{
public:
	NormalInteraction(const int32_t group_vec)
	: m_group_vec(group_vec)
	{}

    template<typename ExtractorF>
	NormalInteraction
	( ExtractorF&& extract
	)
	: NormalInteraction
	  { extract().integer()
	  }
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

	GroupID trigger_group() const { return 0; }
	ProcedureID proc_id_self() const { return ProcedureID(0); }
	ProcedureID proc_id_other() const { return ProcedureID(0); }
	ProcedureID on_exit_proc_id_self() const { return ProcedureID(0); }
	bool triggered() const { return false; }

	void set_trigger_group(GroupID) {}
	void set_proc_id_self(ProcedureID) {}
	void set_proc_id_other(ProcedureID) {}
	void set_on_exit_proc_id_self(ProcedureID) {}

	int32_t last_triggered_groups() const { return 0; }
	int32_t triggered_groups() const { return 0; }
	void set_triggered_groups(int32_t) {}
	void update_last_triggered_groups() {}
	int32_t group_vector() const { return m_group_vec; }

private:
	int32_t m_group_vec;
};

#endif /* COMPONENTS_NORMAL_INTERACTION_H_ */
