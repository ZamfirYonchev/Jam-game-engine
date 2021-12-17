/*
 * play_music_command.h
 *
 *  Created on: Nov 13, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_PLAY_MUSIC_COMMAND_H_
#define COMMANDS_PLAY_MUSIC_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../types.h"
#include <SDL2/SDL_mixer.h>
#include <iostream>

template<typename CommandSystemT, typename ResourceSystemT>
class PlayMusicCommand
{
public:
	CommandSystemT& command_system;
	ResourceSystemT& resource_system;
	Globals& globals;

	PlayMusicCommand(CommandSystemT& _command_system, ResourceSystemT& _resource_system, Globals& _globals)
	: command_system{_command_system}
	, resource_system{_resource_system}
	, globals{_globals}
	{}

    CommandValue operator()() const
    {
    	const auto music_id = command_system.exec_next().integer();
    	const auto loops = command_system.exec_next().integer();

		if(globals(Globals::app_enable_audio).boolean() == false) return CommandValue{music_id};

		if(music_id == -1)
		{
			Mix_HaltMusic();
			return CommandValue{music_id};
		}
		else
		{
			const auto music_optional = resource_system.music(MusicID(music_id));

			if(music_optional)
			{
				if(Mix_PlayMusic(music_optional->get().music(), loops) < 0)
				{
					std::cerr << "Cannot play music " << music_id << ": " << Mix_GetError() << '\n';
				}

				return CommandValue{music_id};
			}
			else
			{
				//error m_sound_id
				return CommandValue{-1.0};
			}
		}
    }
};

#endif /* COMMANDS_PLAY_MUSIC_COMMAND_H_ */
