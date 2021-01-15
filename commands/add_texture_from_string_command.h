/*
 * add_texture_from_string_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_TEXTURE_FROM_STRING_COMMAND_H_
#define COMMANDS_ADD_TEXTURE_FROM_STRING_COMMAND_H_

#include "command_return_value.h"
#include "../types.h"
#include "../systems/resource_system.h"
#include "../systems/rendering_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class AddTextureFromStringCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto font_id = command_system.exec_next();
    	const auto r = command_system.exec_next();
    	const auto g = command_system.exec_next();
    	const auto b = command_system.exec_next();
    	const auto text = command_system.exec_next();

    	if(font_id.integer() < 0)
    	{
			std::cerr << "AddTextureFromStringCommand: font id " << font_id.integer() << " must be >= 0\n";
			return CommandReturnValue{-1.0};
    	}
    	else
    	{
			const auto tex_id = resource_system.addNewTextureFromString(text.string()
														 , FontID(font_id.integer())
														 , r.integer()
														 , g.integer()
														 , b.integer()
														 , rendering_system.renderer());
	    	return CommandReturnValue{static_cast<int64_t>(tex_id)};
    	}
    }
};


#endif /* COMMANDS_ADD_TEXTURE_FROM_STRING_COMMAND_H_ */
