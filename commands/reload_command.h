/*
 * reload_command.h
 *
 *  Created on: Jan 16, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_RELOAD_COMMAND_H_
#define COMMANDS_RELOAD_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"

class ReloadCommand
{
public:
	Globals& globals;
	ReloadCommand(Globals& _globals) : globals{_globals} {}

    CommandValue operator()() const
    {
    	globals(Globals::app_needs_reload) = CommandValue{true};
        std::cout << "Issuing a game reload\n";
        return globals(Globals::app_needs_reload);
    }
};

#endif /* COMMANDS_RELOAD_COMMAND_H_ */
