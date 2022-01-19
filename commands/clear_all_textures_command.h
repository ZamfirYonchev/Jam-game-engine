/*
 * clear_all_textures_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_ALL_TEXTURES_COMMAND_H_
#define COMMANDS_CLEAR_ALL_TEXTURES_COMMAND_H_

#include "../command_value.h"

template<typename TextureResourceSystemT>
class ClearAllTexturesCommand
{
public:
	TextureResourceSystemT& textures;
	ClearAllTexturesCommand(TextureResourceSystemT& _textures)
	: textures{_textures}
	{}

    CommandValue operator()() const
	{
    	textures.clear();
		return CommandValue{0};
	}
};


#endif /* COMMANDS_CLEAR_ALL_TEXTURES_COMMAND_H_ */
