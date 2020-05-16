/*
 * add_texture_from_file_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_texture_from_file_command.h"
#include "../globals.h"

void AddTextureFromFileCommand::execute() const
{
	resource_system().addNewTextureFromFile(m_file, m_renderer);
}
