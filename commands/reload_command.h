/*
 * reload_command.h
 *
 *  Created on: Jan 16, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_RELOAD_COMMAND_H_
#define COMMANDS_RELOAD_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class ReloadCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	globals(Globals::app_needs_reload) = CommandReturnValue{static_cast<int64_t>(1)};
        std::cout << "Issuing a game reload\n";
        return CommandReturnValue{0.0};
    }
};




#endif /* COMMANDS_RELOAD_COMMAND_H_ */
