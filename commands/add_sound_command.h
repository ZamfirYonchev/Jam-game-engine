/*
 * add_sound_command.h
 *
 *  Created on: Nov 13, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_SOUND_COMMAND_H_
#define COMMANDS_ADD_SOUND_COMMAND_H_

#include "command_return_value.h"
#include "../systems/resource_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class AddSoundCommand
{
public:

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto file_name = command_system.exec_next();
    	const auto loops = command_system.exec_next();
    	return static_cast<int64_t>(resource_system.addNewSound(file_name.string(), loops.integer()));
    }
};


#endif /* COMMANDS_ADD_SOUND_COMMAND_H_ */
