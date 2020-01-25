/*
 * debug_message_command.cpp
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#include "debug_message_command.h"
#include <iostream>

void DebugMessageCommand::execute() const
{
	if(m_severity != ERROR)
		std::cout << m_text << std::endl;
	else
		std::cerr << m_text << std::endl;
}

