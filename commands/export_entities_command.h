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
    	const auto file_name = command_system.exec_next();
		std::ofstream file {std::string{file_name.string_view()}};

		if(file)
		{
			const auto print_component_field = [&](const auto& field) { file << field << " "; };

			entity_system.for_each_component_pack([&](const auto&... components) mutable
												  {
													file << "@e AddEntity\n";
													((components.obtain(print_component_field), file << '\n'), ...);
													file << '\n';
												  });
	    	return file_name;
		}
		else
		{
			std::cerr << "Could not open file \"" << file_name.string_view() << "\" for write." << std::endl;
	    	return CommandValue{-1};
		}
	}
};

#endif /* COMMANDS_EXPORT_ENTITIES_COMMAND_H_ */
