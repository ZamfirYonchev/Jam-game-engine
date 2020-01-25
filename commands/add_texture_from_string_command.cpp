/*
 * add_texture_from_string_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_texture_from_string_command.h"
#include "../globals.h"

void AddTextureFromStringCommand::execute() const
{
    globals.resource_system.addNewTextureFromString(m_text, m_font_id, m_r, m_g, m_b, m_renderer);
}
