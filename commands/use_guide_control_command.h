/*
 * use_guide_control_command.h
 *
 *  Created on: Dec 8, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_GUIDE_CONTROL_COMMAND_H_
#define COMMANDS_USE_GUIDE_CONTROL_COMMAND_H_

#include "command.h"
#include "../types.h"

class UseGuideControlCommand : public Command
{
public:
	UseGuideControlCommand(EntityID target_id, ProcedureID attack_proc_id, double attack_cooldown, double attack_range)
	: m_target_id(target_id)
	, m_attack_proc_id(attack_proc_id)
	, m_attack_cooldown(attack_cooldown)
	, m_range(attack_range)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseGuideControlCommand>(m_target_id, m_attack_proc_id, m_attack_cooldown, m_range); }
private:
    EntityID m_target_id;
    ProcedureID m_attack_proc_id;
    double m_attack_cooldown;
    double m_range;
};

#endif /* COMMANDS_USE_GUIDE_CONTROL_COMMAND_H_ */
