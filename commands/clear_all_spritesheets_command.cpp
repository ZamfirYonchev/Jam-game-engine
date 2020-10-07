/*
 * clear_all_spritesheets_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "clear_all_spritesheets_command.h"
#include "../systems/systems.h"
#include "../systems/resource_system.h"

void ClearAllSpritesheetsCommand::execute() const
{
	system<ResourceSystem>().clear_spritesheets();
}
