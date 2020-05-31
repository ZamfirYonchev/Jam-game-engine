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
	if(entity_system().entity(globals().access_entity_id))
		entity_system().entity(globals().access_entity_id)->set_control(new GuideControl(globals().access_entity_id, resolved_entity(m_target_id), m_attack_proc_id, m_attack_cooldown, m_range));
	else
	{
		//error globals().access_entity_id
	}
}

