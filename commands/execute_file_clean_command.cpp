/*
 * execute_file_clean_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "execute_file_clean_command.h"
#include "execute_file_command.h"
#include "../systems/systems.h"
#include "../systems/command_system.h"
#include "../systems/resource_system.h"
#include "../systems/control_system.h"
#include "../systems/movement_system.h"
#include "../systems/collision_system.h"
#include "../systems/damage_system.h"
#include "../systems/rendering_system.h"
#include "../systems/entity_system.h"

void ExecuteFileCleanCommand::execute() const
{
	system<CommandSystem>().flush_commands(false);
	system<ResourceSystem>().clear();
	system<ControlSystem>().clear();
	system<MovementSystem>().clear();
	system<CollisionSystem>().clear();
	system<DamageSystem>().clear();
	system<RenderingSystem>().clear();
	system<EntitySystem>().clear();
	system<CommandSystem>().push(std::make_unique<ExecuteFileCommand>(m_filename, m_renderer));
}
