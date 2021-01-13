/*
 * execute_file_clean_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_EXECUTE_FILE_CLEAN_COMMAND_H_
#define COMMANDS_EXECUTE_FILE_CLEAN_COMMAND_H_

#include "command_return_value.h"
#include "execute_file_command.h"
#include "../systems/resource_system.h"
#include "../systems/rendering_system.h"
#include "literal_value_command.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ExecuteFileCleanCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto file_name = command_system.exec_next();
    	command_system.flush_commands();
    	command_system.clear_procedures();
    	resource_system.clear();
    	rendering_system.clear();
    	all_systems.clear();
    	entity_system.clear();
    	command_system.push(ExecuteFileCommand{});
    	command_system.push(LiteralValueCommand{file_name.string()});

    	return 0.0;
    }
};


#endif /* COMMANDS_EXECUTE_FILE_CLEAN_COMMAND_H_ */
