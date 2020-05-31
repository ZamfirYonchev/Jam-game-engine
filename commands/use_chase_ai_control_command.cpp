/*
 * use_chase_ai_control_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_chase_ai_control_command.h"
#include "../globals.h"
#include "../utilities.h"
#include "../components/chase_ai_control.h"

void UseChaseAIControlCommand::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_control(new ChaseAIControl(entity_system().previous_entity()->id(), resolved_entity(m_target_id), m_attack_id, m_attack_cooldown, m_attack_range));
	else
	{
		//error globals().access_entity_id
	}
}

