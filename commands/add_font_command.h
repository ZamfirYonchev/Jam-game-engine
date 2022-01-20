/*
 * add_font_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_FONT_COMMAND_H_
#define COMMANDS_ADD_FONT_COMMAND_H_

#include "../command_value.h"
#include "../font.h"

template<typename CommandSystemT, typename FontResourceSystemT>
class AddFontCommand
{
public:
	CommandSystemT& command_system;
	FontResourceSystemT& fonts;

	AddFontCommand(CommandSystemT& _command_system, FontResourceSystemT& _fonts)
	: command_system{_command_system}
	, fonts{_fonts}
	{}

    CommandValue operator()() const
    {
    	const std::string file_name = command_system.exec_next();
    	const int font_size = command_system.exec_next();
    	return CommandValue{fonts.add_new(Font{file_name, font_size})};
    }
};

#endif /* COMMANDS_ADD_FONT_COMMAND_H_ */
