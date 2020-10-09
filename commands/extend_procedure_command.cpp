/*
 * extend_procedure_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "extend_procedure_command.h"
#include "../systems/systems.h"
#include "../systems/resource_system.h"
#include "../systems/command_system.h"

void ExtendProcedureCommand::execute() const
{
    if(system<ResourceSystem>().procedure(m_id))
    {
		for(int i = 0; i < m_num_of_cmds; ++i)
		{
			std::unique_ptr<Command> cmd = system<CommandSystem>().pop_next();
			system<ResourceSystem>().procedure(m_id)->add_command(std::move(cmd));
		}
    }
    else
    {
    	//error m_id
    }
}
