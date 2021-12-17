/*
 * execute_file_clean_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_EXECUTE_FILE_CLEAN_COMMAND_H_
#define COMMANDS_EXECUTE_FILE_CLEAN_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "execute_file_command.h"
#include "../systems/resource_system.h"
#include "../systems/rendering_system.h"
#include "literal_value_command.h"

template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT, typename RenderingSystemT, typename ResourceSystemT>
class ExecuteFileCleanCommand
{
public:
	EntitySystemT& entity_system;
	CommandSystemT& command_system;
	AllSystemsT& all_systems;
	RenderingSystemT& rendering_system;
	ResourceSystemT& resource_system;

	ExecuteFileCleanCommand(EntitySystemT& _entity_system, CommandSystemT& _command_system, AllSystemsT& _all_systems, RenderingSystemT& _rendering_system, ResourceSystemT& _resource_system)
	: entity_system{_entity_system}
	, command_system{_command_system}
	, all_systems{_all_systems}
	, rendering_system{_rendering_system}
	, resource_system{_resource_system}
	{}

    CommandValue operator()() const
    {
    	const auto file_name = command_system.exec_next().string();
    	command_system.flush_commands();
    	command_system.clear_procedures();
    	resource_system.clear();
    	rendering_system.clear();
    	all_systems.clear();
    	entity_system.clear();
    	command_system.push(ExecuteFileCommand{command_system});
    	command_system.push(LiteralValueCommand{file_name});

    	return CommandValue{0.0};
    }
};


#endif /* COMMANDS_EXECUTE_FILE_CLEAN_COMMAND_H_ */
