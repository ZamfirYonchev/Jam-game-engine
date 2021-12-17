/*
 * pause_all_sounds_command.h
 *
 *  Created on: Jan 16, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_PAUSE_ALL_SOUNDS_COMMAND_H_
#define COMMANDS_PAUSE_ALL_SOUNDS_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include <SDL2/SDL_mixer.h>

template<typename CommandSystemT>
class PauseAllSoundsCommand
{
public:
	CommandSystemT& command_system;
	Globals& globals;

	PauseAllSoundsCommand(CommandSystemT& _command_system, Globals& _globals)
	: command_system{_command_system}
	, globals{_globals}
	{}

    CommandValue operator()() const
    {
    	const auto paused = command_system.exec_next().boolean();

    	if(globals(Globals::app_enable_audio).boolean() == false) return CommandValue{paused};

    	if(paused)
    	{
    		Mix_Pause(-1);
    		Mix_PauseMusic();
    	}
    	else
    	{
    		Mix_Resume(-1);
    		Mix_ResumeMusic();
    	}

    	return CommandValue{paused};
    }
};

#endif /* COMMANDS_PAUSE_ALL_SOUNDS_COMMAND_H_ */
