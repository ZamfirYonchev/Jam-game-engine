/*
 * add_texture_from_string_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_texture_from_string_command.h"
#include "../systems/systems.h"
#include "../systems/resource_system.h"

void AddTextureFromStringCommand::execute() const
{
	system<ResourceSystem>().addNewTextureFromString(m_text, m_font_id, m_r, m_g, m_b, m_renderer);
}
