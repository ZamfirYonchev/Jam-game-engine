/*
 * spritesheet.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "spritesheet.h"

void Spritesheet::add_sprite(TextureID tex_index, int x, int y, int w, int h)
{
	//assuming that tex_index is inside range
	m_sprites.push_back({tex_index, {x, y, w, h}});
}

