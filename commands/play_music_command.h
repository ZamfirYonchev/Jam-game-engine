/*
 * play_music_command.h
 *
 *  Created on: Nov 13, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_PLAY_MUSIC_COMMAND_H_
#define COMMANDS_PLAY_MUSIC_COMMAND_H_

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
	PlayMusicCommand(const MusicID music_id, const int loops)
	: m_music_id(music_id)
	, m_loops(loops)
	{}

	PlayMusicCommand(const MusicID music_id) : PlayMusicCommand(music_id, -1) {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto music_optional = resource_system.music(m_music_id);
    	if(music_optional)
    	{
    		if(Mix_PlayMusic(music_optional->music(), m_loops) < 0)
    		{
    			std::cerr << "Cannot play music " << m_music_id << ": " << Mix_GetError() << '\n';
    		}
    	}
    	else
    	{
    		//error m_sound_id
    	}
    }

private:
    SoundID m_music_id;
    int m_loops;
};

#endif /* COMMANDS_PLAY_MUSIC_COMMAND_H_ */
