/*
 * interaction.h
 *
 *  Created on: Nov 16, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_INTERACTION_H_
#define COMPONENTS_INTERACTION_H_

#include "../types.h"

class Interaction
{
public:
	static const int NUM_OF_GROUPS = 32;

	virtual ~Interaction() {}

	virtual bool is_in_group(int group_id) const = 0;
	virtual int8_t trigger_group() const = 0;
	virtual bool triggered() const = 0;
	virtual ProcedureID proc_id_self() const = 0;
	virtual ProcedureID proc_id_other() const = 0;
	virtual ProcedureID on_exit_proc_id_self() const = 0;

	virtual void clear_groups() = 0;
	virtual void set_group(int group_id, bool val) = 0;
	virtual void set_trigger_group(int8_t group) = 0;
	virtual void set_triggered(bool triggered) = 0;
	virtual void set_proc_id_self(ProcedureID proc_id) = 0;
	virtual void set_proc_id_other(ProcedureID proc_id) = 0;
	virtual void set_on_exit_proc_id_self(ProcedureID proc_id) = 0;

	static Interaction* null;
};

#endif /* COMPONENTS_INTERACTION_H_ */
