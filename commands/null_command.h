/*
 * null_command.h
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_NULL_COMMAND_H_
#define COMMANDS_NULL_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class NullCommand
{
public:

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	return CommandReturnValue{0.0};
    }
};

#endif /* COMMANDS_NULL_COMMAND_H_ */
