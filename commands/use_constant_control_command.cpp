/*
 * use_constant_control_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "use_constant_control_command.h"
#include "../globals.h"
#include "../components/constant_control.h"

void UseConstantControlCommand::execute() const
{
	if(entity_system().previous_entity())
		entity_system().previous_entity()->set_control(new ConstantControl(m_move_decision, m_jump_decision, m_duck_decision, m_look_dir));
	else
	{
		//error globals().access_entity_id
	}
}
