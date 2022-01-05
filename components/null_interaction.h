/*
 * null_interaction.h
 *
 *  Created on: Nov 16, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_INTERACTION_H_
#define COMPONENTS_NULL_INTERACTION_H_

class NullInteraction
{
public:
	template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseNullInteraction");
    }

    void print(std::ostream& to) const
    {
    	to << "UseNullInteraction ";
    }

    bool is_in_group(int) const { return false; }
	void set_group(int, bool) {}
	void clear_groups() {}
	GroupID trigger_group() const { return 0; }
	bool triggered() const { return false; }
	ProcedureID proc_id_self() const { return ProcedureID(0); }
	ProcedureID proc_id_other() const { return ProcedureID(0); }
	ProcedureID on_exit_proc_id_self() const { return ProcedureID(0); }
	void set_trigger_group(GroupID) {}
	void set_proc_id_self(ProcedureID) {}
	void set_proc_id_other(ProcedureID) {}
	void set_on_exit_proc_id_self(ProcedureID) {}

	int32_t last_triggered_groups() const { return 0; }
	int32_t triggered_groups() const { return 0; }
	void set_triggered_groups(int32_t) {}
	void update_last_triggered_groups() {}
	int32_t group_vector() const { return 0; }
};

#endif /* COMPONENTS_NULL_INTERACTION_H_ */
