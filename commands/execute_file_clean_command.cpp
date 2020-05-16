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
	command_queue().flush_commands();
	resource_system().clear();
	control_system().clear();
	movement_system().clear();
	collision_system().clear();
	damage_system().clear();
	rendering_system().clear();
	entity_system().clear();
	command_queue().push(std::make_unique<ExecuteFileCommand>(m_filename, m_renderer));
}
