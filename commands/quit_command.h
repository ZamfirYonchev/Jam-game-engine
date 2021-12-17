/*
 * quit_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_QUIT_COMMAND_H_
#define COMMANDS_QUIT_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"

class QuitCommand
{
public:
	Globals& globals;
	QuitCommand(Globals& _globals) : globals{_globals} {}

    CommandValue operator()() const
    {
    	globals(Globals::app_running) = CommandValue{false};
        return globals(Globals::app_running);
    }
};


#endif /* COMMANDS_QUIT_COMMAND_H_ */
