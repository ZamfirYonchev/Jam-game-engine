/*
 * export_entities_command.h
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_EXPORT_ENTITIES_COMMAND_H_
#define COMMANDS_EXPORT_ENTITIES_COMMAND_H_

#include <string>
#include <istream>
#include <fstream>
#include <iostream>

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ExportEntitiesCommand
{
public:
	ExportEntitiesCommand(const std::string& filename)
    : m_filename(filename)
    {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		std::ofstream file {m_filename};

		if(file)
			entity_system.for_each([&](const auto& entity){ file << entity << std::endl; });
		else
			std::cerr << "Could not open file " << m_filename << " for write." << std::endl;
	}

private:
    std::string m_filename;
};

#endif /* COMMANDS_EXPORT_ENTITIES_COMMAND_H_ */
