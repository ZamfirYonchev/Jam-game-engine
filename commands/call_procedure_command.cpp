/*
 * call_procedure_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "call_procedure_command.h"
#include "../globals.h"

void CallProcedureCommand::execute() const
{
	if(globals.resource_system.procedure(m_id))
		globals.resource_system.procedure(m_id)->execute();
	else
	{
		//error m_id
	}
}
