/*
 * play_sound_command.h
 *
 *  Created on: Nov 13, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_PLAY_SOUND_COMMAND_H_
#define COMMANDS_PLAY_SOUND_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../types.h"
#include <SDL2/SDL_mixer.h>
#include <iostream>

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class PlaySoundCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto sound_id = command_system.exec_next();
    	const auto channel = command_system.exec_next();

    	const auto sound_optional = resource_system.sound(SoundID(sound_id.integer()));

    	if(sound_optional)
    	{
    		if(Mix_PlayChannel(channel.integer(), sound_optional->get().sound(), sound_optional->get().repeat()) < 0)
    		{
    			std::cerr << "Cannot play sound " << sound_id.integer() << "on channel " << channel.integer() << ": " << Mix_GetError() << '\n';
    		}

        	return CommandReturnValue{0.0};
    	}
    	else
    	{
    		//error m_sound_id
        	return CommandReturnValue{-1l};
    	}
    }
};

#endif /* COMMANDS_PLAY_SOUND_COMMAND_H_ */
