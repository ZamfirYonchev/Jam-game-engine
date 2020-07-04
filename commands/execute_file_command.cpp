/*
 * execute_file_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "execute_file_command.h"
#include <fstream>
#include "../globals.h"

void ExecuteFileCommand::execute() const
{
	std::ifstream file {m_filename};
	if (file)
	{
		std::cout << "Parsing file " << m_filename << std::endl;
		command_queue().process_stream(file, m_renderer, false);
	}
	else
		std::cerr << "File \"" << m_filename << "\" cannot be opened!" << std::endl;
}
