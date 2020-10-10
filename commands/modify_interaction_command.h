/*
 * modify_interaction_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_INTERACTION_COMMAND_H_
#define COMMANDS_MODIFY_INTERACTION_COMMAND_H_

#include "command.h"

class ModifyInteractionCommand : public Command
{
public:
	ModifyInteractionCommand(double group, double value, double trigger_group, double proc_id_self, double on_exit_proc_id_self, double proc_id_other)
	: m_group(group)
	, m_value(value)
	, m_trigger_group(trigger_group)
	, m_proc_id_self(proc_id_self)
	, m_on_exit_proc_id_self(on_exit_proc_id_self)
	, m_proc_id_other(proc_id_other)
	{}

	void execute() const;
	std::unique_ptr<Command> clone() const { return std::make_unique<ModifyInteractionCommand>(m_group, m_value, m_trigger_group, m_proc_id_self, m_on_exit_proc_id_self, m_proc_id_other); }
private:
	double m_group, m_value, m_trigger_group, m_proc_id_self, m_on_exit_proc_id_self, m_proc_id_other;
};

#endif /* COMMANDS_MODIFY_INTERACTION_COMMAND_H_ */
