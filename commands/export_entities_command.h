/*
 * export_entities_command.h
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_EXPORT_ENTITIES_COMMAND_H_
#define COMMANDS_EXPORT_ENTITIES_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include <fstream>
#include <iostream>

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class ExportEntitiesCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto file_name = command_system.exec_next();
		std::ofstream file {file_name.string()};

		if(file)
		{
			entity_system.for_each([&](const auto& entity){ file << entity << std::endl; });
	    	return CommandReturnValue{0.0};
		}
		else
		{
			std::cerr << "Could not open file \"" << file_name.string() << "\" for write." << std::endl;
	    	return CommandReturnValue{-1l};
		}
	}
};

#endif /* COMMANDS_EXPORT_ENTITIES_COMMAND_H_ */
