/*
 * clear_all_procedures_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "clear_all_procedures_command.h"
#include "../systems/systems.h"
#include "../systems/resource_system.h"

void ClearAllProceduresCommand::execute() const
{
	system<ResourceSystem>().clear_procedures();
}
