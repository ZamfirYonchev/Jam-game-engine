/*
 * debug_message_command.h
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_DEBUG_MESSAGE_COMMAND_H_
#define COMMANDS_DEBUG_MESSAGE_COMMAND_H_

#include <string>
#include <iostream>

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class DebugMessageCommand
{
public:
	enum Severity {DEBUG = 0, NOTE = 1, ERROR = 2};
    DebugMessageCommand(const std::string& debug_text, Severity sev)
	: m_text(debug_text)
	, m_severity(sev)
	{}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	if(m_severity != ERROR)
    		std::cout << m_text << std::endl;
    	else
    		std::cerr << m_text << std::endl;
    }

private:
    std::string m_text;
    Severity m_severity;
};


#endif /* COMMANDS_DEBUG_MESSAGE_COMMAND_H_ */
