/*
 * use_input_select_control_command.cpp
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#include "use_input_select_control_command.h"
#include "../globals.h"
#include "../components/input_select_control.h"

void UseInputSelectControlCommand::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_control(new InputSelectControl(&input_handler(), m_select, m_max, m_proc_id));
	else
	{
		//error globals().access_entity_id
	}
}


