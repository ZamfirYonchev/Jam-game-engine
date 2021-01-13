/*
 * add_sprite_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_SPRITE_COMMAND_H_
#define COMMANDS_ADD_SPRITE_COMMAND_H_

#include "command_return_value.h"
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

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto spr_id = command_system.exec_next();
    	const auto tex_id = command_system.exec_next();
    	const auto x = command_system.exec_next();
    	const auto y = command_system.exec_next();
    	const auto w = command_system.exec_next();
    	const auto h = command_system.exec_next();

    	if(spr_id.integer() < 0)
    	{
			std::cerr << "AddSprite: spritesheet id " << spr_id.integer() << " must be >= 0\n";
			return -1.0;
    	}

    	if(tex_id.integer() < 0)
    	{
			std::cerr << "AddSprite: texture id " << tex_id.integer() << " must be >= 0\n";
			return -1.0;
    	}

    	int width, height;
    	if(w.integer() == 0 || h.integer() == 0)
    	{
    		if(resource_system.texture(tex_id.integer()))
    			SDL_QueryTexture(resource_system.texture(tex_id.integer())->texture(), nullptr, nullptr, &width, &height);
    		else
    		{
    			//todo add error message
    			return -1.0;
    		}
    	}

    	width = (w.integer() == 0) ? width  : w.integer();
    	height = (h.integer() == 0) ? height : h.integer();

    	const int sprite_id = resource_system.spritesheet(spr_id.integer())->add_sprite(tex_id.integer(), x.integer(), y.integer(), width, height);

		return static_cast<int64_t>(sprite_id);
    }
};


#endif /* COMMANDS_ADD_SPRITE_COMMAND_H_ */
