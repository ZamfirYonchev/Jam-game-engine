/*
 * stop_all_sounds_command.h
 *
 *  Created on: Jan 30, 2022
 *      Author: zamfi
 */

#ifndef COMMANDS_STOP_ALL_SOUNDS_COMMAND_H_
#define COMMANDS_STOP_ALL_SOUNDS_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include <SDL2/SDL_mixer.h>

template<typename CommandSystemT>
class StopAllSoundsCommand
{
public:
	CommandSystemT& command_system;
	Globals& globals;

	StopAllSoundsCommand(CommandSystemT& _command_system, Globals& _globals)
	: command_system{_command_system}
	, globals{_globals}
	{}

    CommandValue operator()() const
    {
    	if(globals(Globals::app_enable_audio).boolean() == false) return CommandValue{-1};

    	Mix_HaltChannel(-1);

    	return CommandValue{0};
    }
};






#endif /* COMMANDS_STOP_ALL_SOUNDS_COMMAND_H_ */
