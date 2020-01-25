/*
 * select_entity_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "select_entity_command.h"
#include "../globals.h"

void SelectEntityCommand::execute() const
{
    globals.access_entity_id = m_id;
}
