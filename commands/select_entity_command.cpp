/*
 * select_entity_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "select_entity_command.h"
#include "../globals.h"
#include "../utilities.h"

void SelectEntityCommand::execute() const
{
    entity_system().add_accessed_entity(entity_system().resolved_id(m_id));
}
