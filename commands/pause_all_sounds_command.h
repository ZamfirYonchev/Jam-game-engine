/*
 * pause_all_sounds_command.h
 *
 *  Created on: Jan 16, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_PAUSE_ALL_SOUNDS_COMMAND_H_
#define COMMANDS_PAUSE_ALL_SOUNDS_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include <SDL2/SDL_mixer.h>

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class PauseAllSoundsCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto paused = command_system.exec_next();

    	if(globals(Globals::app_enable_audio).boolean() == false) return paused;

    	if(paused.boolean())
    	{
    		Mix_Pause(-1);
    		Mix_PauseMusic();
    	}
    	else
    	{
    		Mix_Resume(-1);
    		Mix_ResumeMusic();
    	}

    	return paused;
    }
};

#endif /* COMMANDS_PAUSE_ALL_SOUNDS_COMMAND_H_ */
