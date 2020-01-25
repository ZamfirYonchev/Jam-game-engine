/*
 * add_sprite_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "add_sprite_command.h"
#include "../globals.h"
#include <SDL2/SDL.h>

void AddSpriteCommand::execute() const
{
	int width, height;
	if(m_w == 0 || m_h == 0)
	{
		SDL_QueryTexture(globals.resource_system.texture(m_tex_id)->texture(), nullptr, nullptr, &width, &height);
	}

	width = (m_w == 0) ? width  : m_w;
	height = (m_h == 0) ? height : m_h;

    globals.resource_system.spritesheet(m_spr_id)->add_sprite(m_tex_id, m_x, m_y, width, height);
}
