/*
 * pause_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "pause_command.h"
#include "../globals.h"

void PauseCommand::execute() const
{
    globals().app_paused = m_paused;
}
