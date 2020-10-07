/*
 * add_font_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_font_command.h"
#include "../systems/systems.h"
#include "../systems/resource_system.h"

void AddFontCommand::execute() const
{
	system<ResourceSystem>().addNewFont(m_file, m_size);
}
