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
#include "../sound_chunk.h"

template<typename CommandSystemT, typename SoundResourceSystemT>
class AddSoundCommand
{
public:
	CommandSystemT& command_system;
	SoundResourceSystemT& sounds;
	Globals& globals;

	AddSoundCommand(CommandSystemT& _command_system, SoundResourceSystemT& _sounds, Globals& _globals)
	: command_system{_command_system}
	, sounds{_sounds}
	, globals{_globals}
	{}

	CommandValue operator()() const
    {
    	const auto file_name = command_system.exec_next().string();
    	const auto loops = command_system.exec_next().integer();

    	if(globals(Globals::app_enable_audio).boolean() == false) return CommandValue{-1};

    	return CommandValue{sounds.add_new(SoundChunk{file_name, loops})};
    }
};


#endif /* COMMANDS_ADD_SOUND_COMMAND_H_ */
