/*
 * clear_all_spritesheets_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "clear_all_spritesheets_command.h"
#include "../globals.h"

void ClearAllSpritesheetsCommand::execute() const
{
	resource_system().clear_spritesheets();
}
