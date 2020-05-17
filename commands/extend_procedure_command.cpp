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
    if(resource_system().procedure(m_id))
    {
		for(int i = 0; i < m_num_of_cmds; ++i)
		{
			std::unique_ptr<Command> cmd = command_queue().pop_next();
			resource_system().procedure(m_id)->add_command(std::move(cmd));
		}
    }
    else
    {
    	//error m_id
    }
}
