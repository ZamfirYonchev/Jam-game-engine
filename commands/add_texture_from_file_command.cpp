/*
 * add_texture_from_file_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_texture_from_file_command.h"
#include "../systems/systems.h"
#include "../systems/resource_system.h"

void AddTextureFromFileCommand::execute() const
{
	system<ResourceSystem>().addNewTextureFromFile(m_file, m_renderer);
}
