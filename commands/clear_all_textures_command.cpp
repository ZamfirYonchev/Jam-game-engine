/*
 * clear_all_textures_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "clear_all_textures_command.h"
#include "../systems/systems.h"
#include "../systems/resource_system.h"

void ClearAllTexturesCommand::execute() const
{
	system<ResourceSystem>().clear_textures();
}
