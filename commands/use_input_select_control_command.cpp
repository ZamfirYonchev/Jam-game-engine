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
	try
	{
		globals.entity_system.entity(globals.access_entity_id).set_control(new InputSelectControl(&globals.input_handler, m_select, m_max, m_proc_id));
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}


