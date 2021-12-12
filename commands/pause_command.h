/*
 * pause_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_PAUSE_COMMAND_H_
#define COMMANDS_PAUSE_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"

template<typename CommandSystemT>
class PauseCommand
{
public:
	CommandSystemT& command_system;
	Globals& globals;

	PauseCommand(CommandSystemT& _command_system, Globals& _globals)
	: command_system{_command_system}
	, globals{_globals}
	{}

    CommandValue operator()() const
    {
    	const auto paused = command_system.exec_next();
    	globals(Globals::app_paused) = paused;
    	return paused;
    }
};


#endif /* COMMANDS_PAUSE_COMMAND_H_ */
