/*
 * use_chase_ai_control_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_CHASE_AI_CONTROL_COMMAND_H_
#define COMMANDS_USE_CHASE_AI_CONTROL_COMMAND_H_

#include "command.h"
#include "../types.h"

class UseChaseAIControlCommand : public Command
{
public:
	UseChaseAIControlCommand(EntityID target_id, ProcedureID attack_id, double attack_cooldown, double attack_range)
	: m_target_id(target_id)
	, m_attack_id(attack_id)
	, m_attack_cooldown(attack_cooldown)
	, m_attack_range(attack_range)
	{}

    void execute() const;
    Command* clone() { return new UseChaseAIControlCommand(m_target_id, m_attack_id, m_attack_cooldown, m_attack_range); }

private:
    EntityID m_target_id;
    ProcedureID m_attack_id;
    double m_attack_cooldown, m_attack_range;
};



#endif /* COMMANDS_USE_CHASE_AI_CONTROL_COMMAND_H_ */
