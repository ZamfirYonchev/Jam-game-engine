/*
 * select_entity_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "select_entity_command.h"
#include "../utilities.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"

void SelectEntityCommand::execute() const
{
    system<EntitySystem>().add_accessed_entity(system<EntitySystem>().resolved_id(m_id));
}
