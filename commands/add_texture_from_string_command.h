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

template<typename CommandSystemT, typename RenderingSystemT, typename ResourceSystemT>
class AddTextureFromStringCommand
{
public:
	CommandSystemT& command_system;
	RenderingSystemT& rendering_system;
	ResourceSystemT& resource_system;

	AddTextureFromStringCommand(CommandSystemT& _command_system, RenderingSystemT& _rendering_system, ResourceSystemT& _resource_system)
	: command_system{_command_system}
	, rendering_system{_rendering_system}
	, resource_system{_resource_system}
	{}

    CommandValue operator()() const
    {
    	const auto font_id = command_system.exec_next();
    	const auto r = command_system.exec_next();
    	const auto g = command_system.exec_next();
    	const auto b = command_system.exec_next();
    	const auto text = command_system.exec_next();

    	if(font_id.integer() < 0)
    	{
			std::cerr << "AddTextureFromStringCommand: font id " << font_id.integer() << " must be >= 0\n";
			return CommandValue{-1.0};
    	}
    	else
    	{
			const auto tex_id = resource_system.addNewTextureFromString(text.string()
														 , FontID(font_id.integer())
														 , r.integer()
														 , g.integer()
														 , b.integer()
														 , rendering_system.renderer());
	    	return CommandValue{tex_id, 0};
    	}
    }
};


#endif /* COMMANDS_ADD_TEXTURE_FROM_STRING_COMMAND_H_ */
