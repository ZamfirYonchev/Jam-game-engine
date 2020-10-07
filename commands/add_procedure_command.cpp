/*
 * add_procedure_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_procedure_command.h"
#include "extend_procedure_command.h"
#include "../systems/systems.h"
#include "../systems/resource_system.h"
#include "../globals.h"

void AddProcedureCommand::execute() const
{
	system<ResourceSystem>().addNewProcedure();
    globals().access_procedure_id = system<ResourceSystem>().last_procedure_id();

    if(m_num_of_cmds > 0)
    {
        ExtendProcedureCommand(globals().access_procedure_id, m_num_of_cmds).execute();
    }
}
