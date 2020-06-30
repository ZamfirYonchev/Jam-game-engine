/*
 * export_entities_command.cpp
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#include "export_entities_command.h"
#include "../globals.h"
#include <fstream>

void ExportEntitiesCommand::execute() const
{
	std::ofstream file {m_filename};

	if(file)
		for(auto& entity : entity_system().entities())
		{
			file << entity << std::endl;
		}
	else
	{
		std::cerr << "Could not open file " << m_filename << " for write." << std::endl;
	}
}
