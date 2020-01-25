/*
 * execute_file_clean_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "execute_file_clean_command.h"
#include "../globals.h"
#include "execute_file_command.h"

void ExecuteFileCleanCommand::execute() const
{
	globals.command_queue.flush_commands();
	globals.resource_system.clear();
	globals.control_system.clear();
	globals.movement_system.clear();
	globals.collision_system.clear();
	globals.damage_system.clear();
	globals.rendering_system.clear();
	globals.entity_system.clear();
	globals.command_queue.push(new ExecuteFileCommand(m_filename, m_renderer));
}
