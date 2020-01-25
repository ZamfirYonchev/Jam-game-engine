/*
 * set_level_command.cpp
 *
 *  Created on: Dec 9, 2019
 *      Author: zamfi
 */

#include "set_level_command.h"
#include "../globals.h"

void SetLevelCommand::execute() const
{
	globals.level_name = m_level;
}
