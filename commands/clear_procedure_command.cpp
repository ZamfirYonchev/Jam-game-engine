/*
 * clear_procedure_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "clear_procedure_command.h"
#include "../globals.h"

void ClearProcedureCommand::execute() const
{
	if(resource_system().procedure(m_id))
	{
		resource_system().procedure(m_id)->clear();
	}
	else
	{
		//error m_id
	}
}
