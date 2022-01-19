/*
 * add_texture_from_file_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_
#define COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_

#include "../command_value.h"
#include "../texture.h"

template<typename CommandSystemT, typename RenderingSystemT, typename TextureResourceSystemT>
class AddTextureFromFileCommand
{
public:
	CommandSystemT& command_system;
	RenderingSystemT& rendering_system;
	TextureResourceSystemT& textures;

	AddTextureFromFileCommand(CommandSystemT& _command_system, RenderingSystemT& _rendering_system, TextureResourceSystemT& _textures)
	: command_system{_command_system}
	, rendering_system{_rendering_system}
	, textures{_textures}
	{}

    CommandValue operator()() const
    {
    	const auto file_name = command_system.exec_next().string();
    	const auto tex_id = textures.add_new(Texture{file_name, rendering_system.renderer()});
    	return CommandValue{tex_id};
    }
};


#endif /* COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_ */
