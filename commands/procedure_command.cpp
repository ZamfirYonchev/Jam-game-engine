/*
 * procedure_command.cpp
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#include "procedure_command.h"
#include "../globals.h"

void ProcedureCommand::execute() const
{
    for(auto it = m_commands.rbegin(); it != m_commands.rend(); ++it)
        globals.command_queue.insert_next((*it)->clone());
}

