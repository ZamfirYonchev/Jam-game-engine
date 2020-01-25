/*
 * quit_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "quit_command.h"
#include "../globals.h"

void QuitCommand::execute() const
{
    globals.app_running = false;
}
