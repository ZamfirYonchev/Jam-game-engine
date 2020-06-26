/*
 * add_procedure_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_procedure_command.h"
#include "../globals.h"
#include "extend_procedure_command.h"

void AddProcedureCommand::execute() const
{
	resource_system().addNewProcedure();
    globals().access_procedure_id = resource_system().last_procedure_id();

    if(m_num_of_cmds > 0)
    {
        ExtendProcedureCommand(globals().access_procedure_id, m_num_of_cmds).execute();
    }
}
