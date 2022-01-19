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
#include "../ref_pack.h"

template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT, typename RenderingSystemT, typename... ResourceSystemsT>
class ExecuteFileCleanCommand
{
public:
	EntitySystemT& entity_system;
	CommandSystemT& command_system;
	AllSystemsT& all_systems;
	RenderingSystemT& rendering_system;
	mutable RefPack<ResourceSystemsT...> resource_systems_pack;

	ExecuteFileCleanCommand(EntitySystemT& _entity_system, CommandSystemT& _command_system, AllSystemsT& _all_systems, RenderingSystemT& _rendering_system, ResourceSystemsT&... _resource_systems)
	: entity_system{_entity_system}
	, command_system{_command_system}
	, all_systems{_all_systems}
	, rendering_system{_rendering_system}
	, resource_systems_pack{_resource_systems...}
	{}

    CommandValue operator()() const
    {
    	const auto file_name = command_system.exec_next();
    	command_system.flush_commands();
    	command_system.clear_procedures();
    	(resource_systems_pack.template access<ResourceSystemsT>().clear(), ...);
    	rendering_system.clear();
    	all_systems.clear();
    	entity_system.clear();
    	command_system.push(ExecuteFileCommand{command_system});
    	command_system.push(LiteralValueCommand{file_name.string_view()});

    	return file_name;
    }
};


#endif /* COMMANDS_EXECUTE_FILE_CLEAN_COMMAND_H_ */
