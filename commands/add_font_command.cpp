/*
 * add_font_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_font_command.h"
#include "../globals.h"

void AddFontCommand::execute() const
{
	resource_system().addNewFont(m_file, m_size);
}
