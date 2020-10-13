/*
 * add_zone_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_ZONE_COMMAND_H_
#define COMMANDS_ADD_ZONE_COMMAND_H_

#include "command.h"
#include "../types.h"
#include "../components/absolute_position.h"

class AddZoneCommand : public Command
{
public:
    AddZoneCommand(const AbsolutePosition& pos, int8_t trigger_group, ProcedureID on_enter_proc_id_self, ProcedureID on_enter_proc_id_other, ProcedureID on_exit_proc_id_self)
	: m_pos(pos)
	, m_trigger_group(trigger_group)
	, m_on_enter_proc_id_self(on_enter_proc_id_self)
	, m_on_enter_proc_id_other(on_enter_proc_id_other)
	, m_on_exit_proc_id_self(on_exit_proc_id_self)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<AddZoneCommand>(m_pos, m_trigger_group, m_on_enter_proc_id_self, m_on_enter_proc_id_other, m_on_exit_proc_id_self); }

private:
    AbsolutePosition m_pos;
    int8_t m_trigger_group;
    ProcedureID m_on_enter_proc_id_self, m_on_enter_proc_id_other, m_on_exit_proc_id_self;
};


#endif /* COMMANDS_ADD_ZONE_COMMAND_H_ */
