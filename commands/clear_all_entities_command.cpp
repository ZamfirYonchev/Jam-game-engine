/*
 * clear_all_entities_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "clear_all_entities_command.h"
#include "../globals.h"

void ClearAllEntitiesCommand::execute() const
{
    globals.entity_system.clear();
}

