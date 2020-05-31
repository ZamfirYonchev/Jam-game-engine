/*
 * use_guide_control_command.cpp
 *
 *  Created on: Dec 8, 2019
 *      Author: zamfi
 */

#include "use_guide_control_command.h"
#include "../globals.h"
#include "../utilities.h"
#include "../components/guide_control.h"

void UseGuideControlCommand::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_control(new GuideControl(entity_system().previous_entity()->id(), resolved_entity(m_target_id), m_attack_proc_id, m_attack_cooldown, m_range));
	else
	{
		//error globals().access_entity_id
	}
}

