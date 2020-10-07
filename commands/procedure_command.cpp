/*
 * procedure_command.cpp
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#include "procedure_command.h"
#include "../systems/systems.h"
#include "../command_queue.h"

void ProcedureCommand::execute() const
{
    for(auto it = m_commands.rbegin(); it != m_commands.rend(); ++it)
    	system<CommandQueue>().insert_next((*it)->clone());
}

