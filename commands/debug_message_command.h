/*
 * debug_message_command.h
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_DEBUG_MESSAGE_COMMAND_H_
#define COMMANDS_DEBUG_MESSAGE_COMMAND_H_

#include "command.h"
#include <string>

class DebugMessageCommand : public Command
{
public:
	enum Severity {DEBUG = 0, NOTE = 1, ERROR = 2};
    DebugMessageCommand(const std::string& debug_text, Severity sev)
	: m_text(debug_text)
	, m_severity(sev)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<DebugMessageCommand>(m_text, m_severity); }

private:
    std::string m_text;
    Severity m_severity;
};


#endif /* COMMANDS_DEBUG_MESSAGE_COMMAND_H_ */
