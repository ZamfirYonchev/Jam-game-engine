/*
 * add_sprite_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_SPRITE_COMMAND_H_
#define COMMANDS_ADD_SPRITE_COMMAND_H_

#include "../command_value.h"
#include "../types.h"
#include <SDL2/SDL.h>

template<typename CommandSystemT, typename ResourceSystemT>
class AddSpriteCommand
{
public:
	CommandSystemT& command_system;
	ResourceSystemT& resource_system;

	AddSpriteCommand(CommandSystemT& _command_system, ResourceSystemT& _resource_system)
	: command_system{_command_system}
	, resource_system{_resource_system}
	{}

	CommandValue operator()() const
    {
    	const auto anim_id = command_system.exec_next();
    	const auto tex_id = command_system.exec_next();
    	const auto x = command_system.exec_next();
    	const auto y = command_system.exec_next();
    	const auto w = command_system.exec_next();
    	const auto h = command_system.exec_next();

    	if(anim_id.integer() < 0)
    	{
			std::cerr << "AddSprite: animation id " << anim_id.integer() << " must be >= 0\n";
			return CommandValue{-1.0};
    	}

    	if(tex_id.integer() < 0)
    	{
			std::cerr << "AddSprite: texture id " << tex_id.integer() << " must be >= 0\n";
			return CommandValue{-1.0};
    	}

    	int width = 0, height = 0;
    	if(w.integer() == 0 || h.integer() == 0)
    	{
    		if(resource_system.texture(tex_id.integer()))
    			SDL_QueryTexture(resource_system.texture(tex_id.integer())->get().texture(), nullptr, nullptr, &width, &height);
    		else
    		{
    			//todo add error message
    			return CommandValue{-1.0};
    		}
    	}

    	width = (w.integer() == 0) ? width  : w.integer();
    	height = (h.integer() == 0) ? height : h.integer();

    	const int sprite_id = resource_system.animation(anim_id.integer())->get().add_sprite({TextureID(tex_id.integer()), {int(x.integer()), int(y.integer()), width, height}});

		return CommandValue{sprite_id, 0};
    }
};


#endif /* COMMANDS_ADD_SPRITE_COMMAND_H_ */
