/*
 * clear_all_procedures_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "clear_all_procedures_command.h"
#include "../globals.h"

void ClearAllProceduresCommand::execute() const
{
	resource_system().clear_procedures();
}
