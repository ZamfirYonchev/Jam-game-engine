/*
 * debug_message_command.h
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_DEBUG_MESSAGE_COMMAND_H_
#define COMMANDS_DEBUG_MESSAGE_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "debug_message_enums.h"
#include <iostream>

template<typename CommandSystemT>
class DebugMessageCommand
{
public:

	CommandSystemT& command_system;
	Globals& globals;

	DebugMessageCommand(CommandSystemT& _command_system, Globals& _globals)
	: command_system{_command_system}
	, globals{_globals}
	{}

    CommandValue operator()() const
    {
    	const auto severity = command_system.exec_next();
    	const auto text = command_system.exec_next();

    	if(severity.integer() == int(Severity::FATAL))
    	{
    		std::cerr << "FATAL: " << text.string() << std::endl;
    		command_system.flush_commands();
    	}
    	else if(severity.integer() == int(Severity::ERROR))
    	{
    		std::cerr << "ERROR: " << text.string() << std::endl;
    	}
    	else if(globals(Globals::app_debug_level).integer() >= severity.integer())
    	{
    		std::cout << text.string() << std::endl;
    	}

    	return CommandValue{0.0};
    }
};


#endif /* COMMANDS_DEBUG_MESSAGE_COMMAND_H_ */
