/*
 * clear_all_textures_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "clear_all_textures_command.h"
#include "../globals.h"

void ClearAllTexturesCommand::execute() const
{
    globals.resource_system.clear_textures();
}
