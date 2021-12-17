/*
 * add_texture_from_file_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_
#define COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_

#include "../command_value.h"

template<typename CommandSystemT, typename RenderingSystemT, typename ResourceSystemT>
class AddTextureFromFileCommand
{
public:
	CommandSystemT& command_system;
	RenderingSystemT& rendering_system;
	ResourceSystemT& resource_system;

	AddTextureFromFileCommand(CommandSystemT& _command_system, RenderingSystemT& _rendering_system, ResourceSystemT& _resource_system)
	: command_system{_command_system}
	, rendering_system{_rendering_system}
	, resource_system{_resource_system}
	{}

    CommandValue operator()() const
    {
    	const auto file_name = command_system.exec_next().string();
    	const auto tex_id = resource_system.addNewTextureFromFile(file_name, rendering_system.renderer());
    	return CommandValue{tex_id};
    }
};


#endif /* COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_ */
