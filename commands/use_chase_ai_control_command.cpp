/*
 * use_chase_ai_control_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_chase_ai_control_command.h"
#include "../globals.h"
#include "../components/chase_ai_control.h"

void UseChaseAIControlCommand::execute() const
{
	globals.entity_system.entity(globals.access_entity_id)->set_control(new ChaseAIControl(globals.access_entity_id, m_target_id, m_attack_id, m_attack_cooldown, m_attack_range));
}

