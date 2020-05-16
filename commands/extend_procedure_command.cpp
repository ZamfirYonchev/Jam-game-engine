/*
 * extend_procedure_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "extend_procedure_command.h"
#include "../globals.h"

void ExtendProcedureCommand::execute() const
{
	try
	{
		for(int i = 0; i < m_num_of_cmds; ++i)
		{
			std::unique_ptr<Command> cmd = globals.command_queue.pop_next();
			globals.resource_system.procedure(m_id).add_command(std::move(cmd));
		}
	}
	catch(std::out_of_range& except)
	{
		//error message
	}
}
