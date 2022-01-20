/*
 * add_texture_from_string_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_TEXTURE_FROM_STRING_COMMAND_H_
#define COMMANDS_ADD_TEXTURE_FROM_STRING_COMMAND_H_

#include "../command_value.h"
#include "../types.h"
#include "../texture.h"

template<typename CommandSystemT, typename RenderingSystemT, typename TextureResourceSystemT, typename FontResourceSystemT>
class AddTextureFromStringCommand
{
public:
	CommandSystemT& command_system;
	RenderingSystemT& rendering_system;
	TextureResourceSystemT& textures;
	FontResourceSystemT& fonts;

	AddTextureFromStringCommand(CommandSystemT& _command_system, RenderingSystemT& _rendering_system, TextureResourceSystemT& _textures, FontResourceSystemT& _fonts)
	: command_system{_command_system}
	, rendering_system{_rendering_system}
	, textures{_textures}
	, fonts{_fonts}
	{}

    CommandValue operator()() const
    {
    	const FontID font_id = command_system.exec_next();
    	const uint8_t r = command_system.exec_next();
    	const uint8_t g = command_system.exec_next();
    	const uint8_t b = command_system.exec_next();
    	const std::string text = command_system.exec_next();

    	const auto font_opt = fonts[font_id];

    	if(font_opt)
    	{
    		const auto tex_id = textures.add_new(Texture
    											 { text
    											 , font_opt->get()
												 , r
												 , g
												 , b
												 , rendering_system.renderer()
    											 });
	    	return CommandValue{tex_id};
    	}
    	else
    	{
			std::cerr << "AddTextureFromStringCommand: font id " << font_id << " must be in valid range\n";
			return CommandValue{-1};
    	}
    }
};


#endif /* COMMANDS_ADD_TEXTURE_FROM_STRING_COMMAND_H_ */
