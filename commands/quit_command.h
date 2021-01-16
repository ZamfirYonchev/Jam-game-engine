/*
 * quit_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_QUIT_COMMAND_H_
#define COMMANDS_QUIT_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class QuitCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	globals(Globals::app_running) = CommandReturnValue{0l};
        return CommandReturnValue{0l};
    }
};


#endif /* COMMANDS_QUIT_COMMAND_H_ */
