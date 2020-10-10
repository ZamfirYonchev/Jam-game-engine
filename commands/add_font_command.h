/*
 * add_font_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_FONT_COMMAND_H_
#define COMMANDS_ADD_FONT_COMMAND_H_

#include "command.h"
#include <string>

class AddFontCommand : public Command
{
public:
	AddFontCommand(const std::string& file, int size)
	: m_file(file)
	, m_size(size)
	{}
    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<AddFontCommand>(m_file, m_size); }

private:
    std::string m_file;
    int m_size;
};


#endif /* COMMANDS_ADD_FONT_COMMAND_H_ */
