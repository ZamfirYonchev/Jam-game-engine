/*
 * use_trigger_interaction_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_TRIGGER_INTERACTION_COMMAND_H_
#define COMMANDS_USE_TRIGGER_INTERACTION_COMMAND_H_

#include "command.h"
#include "cinttypes"
#include "../types.h"

class UseTriggerInteractionCommand : public Command
{
public:
	UseTriggerInteractionCommand(int8_t trigger_group, ProcedureID on_enter_proc_id_self, ProcedureID on_exit_proc_id_self, ProcedureID on_enter_proc_id_other)
	: m_trigger_group(trigger_group)
	, m_on_enter_proc_id_self(on_enter_proc_id_self)
	, m_on_exit_proc_id_self(on_exit_proc_id_self)
	, m_on_enter_proc_id_other(on_enter_proc_id_other)
	{}

	void execute() const;
    Command* clone() { return new UseTriggerInteractionCommand(m_trigger_group, m_on_enter_proc_id_self, m_on_exit_proc_id_self, m_on_enter_proc_id_other); }

private:
    int8_t m_trigger_group;
    ProcedureID m_on_enter_proc_id_self, m_on_exit_proc_id_self, m_on_enter_proc_id_other;
};

#endif /* COMMANDS_USE_TRIGGER_INTERACTION_COMMAND_H_ */
