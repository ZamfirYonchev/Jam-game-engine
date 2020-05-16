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
	try
	{
		globals.resource_system.procedure(m_id).execute();
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}
