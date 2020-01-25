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
    for(int i = 0; i < m_num_of_cmds; ++i)
    {
        Command* cmd = globals.command_queue.pop_next();
        globals.resource_system.procedure(m_id)->add_command(cmd);
    }
}
