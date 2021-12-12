/*
 * add_font_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_FONT_COMMAND_H_
#define COMMANDS_ADD_FONT_COMMAND_H_

#include "../command_value.h"

template<typename CommandSystemT, typename ResourceSystemT>
class AddFontCommand
{
public:
	CommandSystemT& command_system;
	ResourceSystemT& resource_system;

	AddFontCommand(CommandSystemT& _command_system, ResourceSystemT& _resource_system)
	: command_system{_command_system}
	, resource_system{_resource_system}
	{}

    CommandValue operator()() const
    {
    	const auto file_name = command_system.exec_next();
    	const auto font_size = command_system.exec_next();
    	return CommandValue{resource_system.addNewFont(file_name.string(), font_size.integer()), 0};
    }
};

#endif /* COMMANDS_ADD_FONT_COMMAND_H_ */
