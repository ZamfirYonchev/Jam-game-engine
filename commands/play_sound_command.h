/*
 * play_sound_command.h
 *
 *  Created on: Nov 13, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_PLAY_SOUND_COMMAND_H_
#define COMMANDS_PLAY_SOUND_COMMAND_H_

#include "../types.h"
#include <SDL2/SDL_mixer.h>
#include <iostream>

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class PlaySoundCommand
{
public:
	PlaySoundCommand(const SoundID sound_id, const int loops, const int channel)
	: m_sound_id(sound_id)
	, m_loops(loops)
	, m_channel(channel)
	{}

	PlaySoundCommand(const SoundID sound_id, const int loops) : PlaySoundCommand(sound_id, loops, -1) {}
	PlaySoundCommand(const SoundID sound_id) : PlaySoundCommand(sound_id, -1, -1) {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto sound_optional = resource_system.sound(m_sound_id);
    	if(sound_optional)
    	{
    		if(Mix_PlayChannel(m_channel, sound_optional->sound(), m_loops) < 0)
    		{
    			std::cerr << "Cannot play sound " << m_sound_id << ": " << Mix_GetError() << '\n';
    		}
    	}
    	else
    	{
    		//error m_sound_id
    	}
    }

private:
    SoundID m_sound_id;
    int m_loops, m_channel;
};

#endif /* COMMANDS_PLAY_SOUND_COMMAND_H_ */
