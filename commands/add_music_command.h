/*
 * add_music_command.h
 *
 *  Created on: Nov 13, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_MUSIC_COMMAND_H_
#define COMMANDS_ADD_MUSIC_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../music.h"

template<typename CommandSystemT, typename MusicResourceSystemT>
class AddMusicCommand
{
public:
	CommandSystemT& command_system;
	MusicResourceSystemT& music;
	Globals& globals;

	AddMusicCommand(CommandSystemT& _command_system, MusicResourceSystemT& _music, Globals& _globals)
	: command_system{_command_system}
	, music{_music}
	, globals{_globals}
	{}

	CommandValue operator()() const
    {
    	const std::string file_name = command_system.exec_next();

    	if(globals(Globals::app_enable_audio).boolean() == false) return CommandValue{-1};

    	return CommandValue{music.add_new(Music{file_name})};
    }
};


#endif /* COMMANDS_ADD_MUSIC_COMMAND_H_ */
