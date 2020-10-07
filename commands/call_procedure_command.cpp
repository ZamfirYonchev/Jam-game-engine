/*
 * call_procedure_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "call_procedure_command.h"
#include "../systems/systems.h"
#include "../systems/resource_system.h"

void CallProcedureCommand::execute() const
{
	if(system<ResourceSystem>().procedure(m_id))
		system<ResourceSystem>().procedure(m_id)->execute();
	else
	{
		//error m_id
	}
}
