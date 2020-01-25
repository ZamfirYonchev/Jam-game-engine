/*
 * set_level_command.h
 *
 *  Created on: Dec 9, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_SET_LEVEL_COMMAND_H_
#define COMMANDS_SET_LEVEL_COMMAND_H_

#include "command.h"
#include <string>

class SetLevelCommand : public Command
{
public:
	SetLevelCommand(const std::string& level)
	: m_level(level)
	{}

    void execute() const;
    Command* clone() { return new SetLevelCommand(m_level); }

private:
    std::string m_level;
};




#endif /* COMMANDS_SET_LEVEL_COMMAND_H_ */
