/*
 * null_interaction.h
 *
 *  Created on: Nov 16, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_INTERACTION_H_
#define COMPONENTS_NULL_INTERACTION_H_

#include "interaction.h"

class NullInteraction : public Interaction
{
public:
	using Base = Interaction;
    void print(std::ostream& to) const
    {
    	to << "UseNullInteraction ";
    }

    bool is_in_group(int group_id) const { return false; }
	void set_group(int group_id, bool val) {}
	void clear_groups() {}
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
};

#endif /* COMPONENTS_NULL_INTERACTION_H_ */
