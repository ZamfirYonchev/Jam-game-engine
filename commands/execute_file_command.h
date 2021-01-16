/*
 * execute_file_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_EXECUTE_FILE_COMMAND_H_
#define COMMANDS_EXECUTE_FILE_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include <fstream>
#include <iostream>

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class ExecuteFileCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto file_name = command_system.exec_next();
    	std::ifstream file {file_name.string()};
    	if (file)
    	{
    		std::cout << "Parsing file " << file_name.string() << std::endl;
    		command_system.process_stream(file);
    		return CommandReturnValue{0l};
    	}
    	else
    	{
    		std::cerr << "File \"" << file_name.string() << "\" cannot be opened!" << std::endl;
    		return CommandReturnValue{-1l};
    	}
    }
};


#endif /* COMMANDS_EXECUTE_FILE_COMMAND_H_ */
