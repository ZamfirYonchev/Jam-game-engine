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
    	const AnimationID anim_id = command_system.exec_next();
    	const TextureID tex_id = command_system.exec_next();
    	const int x = command_system.exec_next();
    	const int y = command_system.exec_next();
    	int w = command_system.exec_next();
    	int h = command_system.exec_next();

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

    	if(w == 0 || h == 0)
    	{
    		if(textures[tex_id])
    			SDL_QueryTexture(textures[tex_id]->get().texture(), nullptr, nullptr, &w, &h);
    		else
    		{
    			//todo add error message
    			return CommandValue{-1};
    		}
    	}

    	const auto anim_opt = animations[anim_id];
    	if(anim_opt)
    	{
        	const int sprite_id = anim_opt->get().add_sprite({TextureID(tex_id), {x, y, w, h}});
    		return CommandValue{sprite_id};
    	}
    	else
    	{
			//todo add error message
			return CommandValue{-1};
    	}
    }
};


#endif /* COMMANDS_ADD_SPRITE_COMMAND_H_ */
