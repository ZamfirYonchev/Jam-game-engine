/*
 * play_sound_command.h
 *
 *  Created on: Nov 13, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_PLAY_SOUND_COMMAND_H_
#define COMMANDS_PLAY_SOUND_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../types.h"
#include <SDL2/SDL_mixer.h>
#include <iostream>

template<typename CommandSystemT, typename ResourceSystemT>
class PlaySoundCommand
{
public:
	CommandSystemT& command_system;
	ResourceSystemT& resource_system;
	Globals& globals;

	PlaySoundCommand(CommandSystemT& _command_system, ResourceSystemT& _resource_system, Globals& _globals)
	: command_system{_command_system}
	, resource_system{_resource_system}
	, globals{_globals}
	{}

    CommandValue operator()() const
    {
    	const auto sound_id = command_system.exec_next();
    	const auto channel = command_system.exec_next();

		if(globals(Globals::app_enable_audio).boolean() == false) return sound_id;

		const auto sound_optional = resource_system.sound(SoundID(sound_id.integer()));

    	if(sound_optional)
    	{
    		if(Mix_PlayChannel(channel.integer(), sound_optional->get().sound(), sound_optional->get().repeat()) < 0)
    		{
    			std::cerr << "Cannot play sound " << sound_id.integer() << " on channel " << channel.integer() << ": " << Mix_GetError() << '\n';
    		}

        	return sound_id;
    	}
    	else
    	{
    		//error m_sound_id
        	return CommandValue{-1.0};
    	}
    }
};

#endif /* COMMANDS_PLAY_SOUND_COMMAND_H_ */
