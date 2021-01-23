/*
 * debug_message_command.h
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_DEBUG_MESSAGE_COMMAND_H_
#define COMMANDS_DEBUG_MESSAGE_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include <iostream>

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class DebugMessageCommand
{
public:
	enum class Severity {FATAL = -2, ERROR = -1, NOTE = 0, DEBUG = 1, };

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
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

    	return CommandReturnValue{0.0};
    }
};


#endif /* COMMANDS_DEBUG_MESSAGE_COMMAND_H_ */
