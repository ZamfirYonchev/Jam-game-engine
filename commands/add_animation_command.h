/*
 * add_animation_command.h
 *
 *  Created on: Jan 17, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_ANIMATION_COMMAND_H_
#define COMMANDS_ADD_ANIMATION_COMMAND_H_

#include <string>
#include "command_return_value.h"
#include "../globals.h"
#include "../systems/resource_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class AddAnimationCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto frame_delay_ms = command_system.exec_next();
    	const auto scale_factor = command_system.exec_next();
    	return CommandReturnValue{resource_system.addNewAnimation({frame_delay_ms.integer(), scale_factor.real()}), 0};
    }
};

#endif /* COMMANDS_ADD_ANIMATION_COMMAND_H_ */
