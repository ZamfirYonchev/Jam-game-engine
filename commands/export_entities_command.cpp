/*
 * export_entities_command.cpp
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#include "export_entities_command.h"
#include <fstream>
#include <iostream>
#include "../systems/systems.h"
#include "../systems/entity_system.h"

void ExportEntitiesCommand::execute() const
{
	std::ofstream file {m_filename};

	if(file)
		system<EntitySystem>().for_each([&](const auto& entity){ file << entity << std::endl; });
	else
		std::cerr << "Could not open file " << m_filename << " for write." << std::endl;
}
