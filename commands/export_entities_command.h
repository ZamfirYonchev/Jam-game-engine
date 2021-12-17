/*
 * export_entities_command.h
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_EXPORT_ENTITIES_COMMAND_H_
#define COMMANDS_EXPORT_ENTITIES_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include <fstream>
#include <iostream>

template<typename CommandSystemT, typename EntitySystemT>
class ExportEntitiesCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;

	ExportEntitiesCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system)
	: command_system{_command_system}
	, entity_system{_entity_system}
	{}

    CommandValue operator()() const
	{
    	const auto file_name = command_system.exec_next().string();
		std::ofstream file {std::string{file_name}};

		if(file)
		{
			entity_system.for_each_component_pack([&](const auto&... components)
												  {
													file << "@e AddEntity\n";
													(file << ... << components);
													file << '\n';
												  });
	    	return CommandValue{0.0};
		}
		else
		{
			std::cerr << "Could not open file \"" << std::string_view{file_name} << "\" for write." << std::endl;
	    	return CommandValue{-1.0};
		}
	}
};

#endif /* COMMANDS_EXPORT_ENTITIES_COMMAND_H_ */
