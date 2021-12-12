/*
 * add_sound_command.h
 *
 *  Created on: Nov 13, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_SOUND_COMMAND_H_
#define COMMANDS_ADD_SOUND_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"

template<typename CommandSystemT, typename ResourceSystemT>
class AddSoundCommand
{
public:
	CommandSystemT& command_system;
	ResourceSystemT& resource_system;
	Globals& globals;

	AddSoundCommand(CommandSystemT& _command_system, ResourceSystemT& _resource_system, Globals& _globals)
	: command_system{_command_system}
	, resource_system{_resource_system}
	, globals{_globals}
	{}

	CommandValue operator()() const
    {
    	const auto file_name = command_system.exec_next();
    	const auto loops = command_system.exec_next();

    	if(globals(Globals::app_enable_audio).boolean() == false) return CommandValue{-1.0};

    	return CommandValue{resource_system.addNewSound(file_name.string(), loops.integer()), 0};
    }
};


#endif /* COMMANDS_ADD_SOUND_COMMAND_H_ */
