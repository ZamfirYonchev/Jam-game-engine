/*
 * execute_file_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_EXECUTE_FILE_COMMAND_H_
#define COMMANDS_EXECUTE_FILE_COMMAND_H_

#include <string>
#include <fstream>
#include "../systems/command_system.h"
#include <iostream>

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ExecuteFileCommand
{
public:
    ExecuteFileCommand(const std::string& filename)
    : m_filename(filename)
    {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	std::ifstream file {m_filename};
    	if (file)
    	{
    		std::cout << "Parsing file " << m_filename << std::endl;
    		command_system.process_stream(file);
    	}
    	else
    		std::cerr << "File \"" << m_filename << "\" cannot be opened!" << std::endl;
    }

private:
    std::string m_filename;
};


#endif /* COMMANDS_EXECUTE_FILE_COMMAND_H_ */
