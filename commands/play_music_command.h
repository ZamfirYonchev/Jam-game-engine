/*
 * play_music_command.h
 *
 *  Created on: Nov 13, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_PLAY_MUSIC_COMMAND_H_
#define COMMANDS_PLAY_MUSIC_COMMAND_H_

#include "command_return_value.h"
#include "../types.h"
#include <SDL2/SDL_mixer.h>
#include <iostream>

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class PlayMusicCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto music_id = command_system.exec_next();
    	const auto loops = command_system.exec_next();

    	const auto music_optional = resource_system.music(MusicID(music_id.integer()));

    	if(music_optional)
    	{
    		if(Mix_PlayMusic(music_optional->music(), loops.integer()) < 0)
    		{
    			std::cerr << "Cannot play music " << music_id.integer() << ": " << Mix_GetError() << '\n';
    		}

        	return CommandReturnValue{0.0};
    	}
    	else
    	{
    		//error m_sound_id
        	return CommandReturnValue{-1.0};
    	}
    }
};

#endif /* COMMANDS_PLAY_MUSIC_COMMAND_H_ */
