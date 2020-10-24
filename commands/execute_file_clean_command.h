/*
 * execute_file_clean_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_EXECUTE_FILE_CLEAN_COMMAND_H_
#define COMMANDS_EXECUTE_FILE_CLEAN_COMMAND_H_

#include <string>
#include "execute_file_command.h"
#include "../systems/resource_system.h"
#include "../systems/rendering_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ExecuteFileCleanCommand
{
public:
    ExecuteFileCleanCommand(const std::string& filename)
    : m_filename(filename)
    {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	command_system.flush_commands();
    	command_system.clear_procedures();
    	resource_system.clear();
    	rendering_system.clear();
    	all_systems.clear();
    	entity_system.clear();
    	ExecuteFileCommand{m_filename}(entity_system, resource_system, input_system, command_system, rendering_system, all_systems, globals);
    }

private:
    std::string m_filename;
};


#endif /* COMMANDS_EXECUTE_FILE_CLEAN_COMMAND_H_ */
