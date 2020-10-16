/*
 * add_spritesheet_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_spritesheet_command.h"
#include "../systems/systems.h"
#include "../systems/resource_system.h"
#include "../globals.h"

void AddSpritesheetCommand::execute() const
{
	system<ResourceSystem>().addNewSpritesheet(m_spritesheet);
    globals().access_spritesheet_id = system<ResourceSystem>().last_spritesheet_id();
}
