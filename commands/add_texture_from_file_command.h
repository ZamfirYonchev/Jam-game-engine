/*
 * add_texture_from_file_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_
#define COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../systems/resource_system.h"
#include "../systems/rendering_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class AddTextureFromFileCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto file_name = command_system.exec_next();
    	const auto tex_id = resource_system.addNewTextureFromFile(file_name.string(), rendering_system.renderer());
    	return CommandReturnValue{tex_id, 0};
    }
};


#endif /* COMMANDS_ADD_TEXTURE_FROM_FILE_COMMAND_H_ */
