/*
 * execute_file_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_EXECUTE_FILE_COMMAND_H_
#define COMMANDS_EXECUTE_FILE_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include <fstream>
#include <iostream>

template<typename CommandSystemT>
class ExecuteFileCommand
{
public:
	CommandSystemT& command_system;
	ExecuteFileCommand(CommandSystemT& _command_system)
	: command_system{_command_system}
	{}

    CommandValue operator()() const
    {
    	const auto file_name = command_system.exec_next().string();
    	std::ifstream file {std::string{file_name}};
    	if (file)
    	{
    		std::cout << "Parsing file " << file_name << std::endl;
    		command_system.parse(file);
    		return CommandValue{file_name};
    	}
    	else
    	{
    		std::cerr << "File \"" << file_name << "\" cannot be opened!" << std::endl;
    		return CommandValue{-1};
    	}
    }
};


#endif /* COMMANDS_EXECUTE_FILE_COMMAND_H_ */
