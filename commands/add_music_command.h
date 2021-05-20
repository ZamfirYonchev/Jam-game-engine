/*
 * add_music_command.h
 *
 *  Created on: Nov 13, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_MUSIC_COMMAND_H_
#define COMMANDS_ADD_MUSIC_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../systems/resource_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class AddMusicCommand
{
public:

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto file_name = command_system.exec_next();

    	if(globals(Globals::app_enable_audio).boolean() == false) return CommandReturnValue{-1.0};

    	return CommandReturnValue{resource_system.addNewMusic(file_name.string()), 0};
    }
};


#endif /* COMMANDS_ADD_MUSIC_COMMAND_H_ */
