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

template<typename CommandSystemT, typename TextureResourceSystemT, typename AnimationResourceSystemT>
class AddSpriteCommand
{
public:
	CommandSystemT& command_system;
	TextureResourceSystemT& textures;
	AnimationResourceSystemT& animations;

	AddSpriteCommand(CommandSystemT& _command_system, TextureResourceSystemT& _textures, AnimationResourceSystemT& _animations)
	: command_system{_command_system}
	, textures{_textures}
	, animations{_animations}
	{}

	CommandValue operator()() const
    {
    	const auto anim_id = command_system.exec_next().integer();
    	const auto tex_id = command_system.exec_next().integer();
    	const auto x = command_system.exec_next().integer();
    	const auto y = command_system.exec_next().integer();
    	const auto w = command_system.exec_next().real();
    	const auto h = command_system.exec_next().real();

    	if(anim_id < 0)
    	{
			std::cerr << "AddSprite: animation id " << anim_id << " must be >= 0\n";
			return CommandValue{-1};
    	}

    	if(tex_id < 0)
    	{
			std::cerr << "AddSprite: texture id " << tex_id << " must be >= 0\n";
			return CommandValue{-1};
    	}

    	int width = 0, height = 0;
    	if(w == 0 || h == 0)
    	{
    		if(textures[tex_id])
    			SDL_QueryTexture(textures[tex_id]->get().texture(), nullptr, nullptr, &width, &height);
    		else
    		{
    			//todo add error message
    			return CommandValue{-1};
    		}
    	}

    	width = (w == 0) ? width  : w;
    	height = (h == 0) ? height : h;

    	const int sprite_id = animations[anim_id]->get().add_sprite({TextureID(tex_id), {x, y, width, height}});

		return CommandValue{sprite_id};
    }
};


#endif /* COMMANDS_ADD_SPRITE_COMMAND_H_ */
