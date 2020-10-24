/*
 * add_sprite_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_SPRITE_COMMAND_H_
#define COMMANDS_ADD_SPRITE_COMMAND_H_

#include "../types.h"
#include <SDL2/SDL.h>
#include "../systems/resource_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class AddSpriteCommand
{
public:
    AddSpriteCommand(AbsSpritesheetID spr_id, AbsTextureID tex_id, int x, int y, int w, int h)
    : m_spr_id(spr_id)
    , m_tex_id(tex_id)
    , m_x(x)
    , m_y(y)
    , m_w(w)
    , m_h(h)
    {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	int width, height;
    	if(m_w == 0 || m_h == 0)
    	{
    		if(resource_system.texture(m_tex_id))
    			SDL_QueryTexture(resource_system.texture(m_tex_id)->texture(), nullptr, nullptr, &width, &height);
    		else
    		{
    			//todo add error message
    			return;
    		}
    	}

    	width = (m_w == 0) ? width  : m_w;
    	height = (m_h == 0) ? height : m_h;

    	resource_system.spritesheet(m_spr_id)->add_sprite(m_tex_id, m_x, m_y, width, height);
    }

private:
    AbsSpritesheetID m_spr_id;
    AbsTextureID m_tex_id;
    int m_x, m_y, m_w, m_h;
};


#endif /* COMMANDS_ADD_SPRITE_COMMAND_H_ */
