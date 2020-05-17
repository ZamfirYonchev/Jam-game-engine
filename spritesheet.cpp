/*
 * spritesheet.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "spritesheet.h"
#include "globals.h"

void Spritesheet::add_sprite(TextureID tex_index, int x, int y, int w, int h)
{
    if(tex_index < resource_system().textures().size())
    {
        m_sprites.push_back({tex_index, {x, y, w, h}});
    }
    else
    {
    	//error tex_index
    }
}

