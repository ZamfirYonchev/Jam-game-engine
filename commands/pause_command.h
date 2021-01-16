/*
 * pause_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_PAUSE_COMMAND_H_
#define COMMANDS_PAUSE_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class PauseCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto paused = command_system.exec_next();
    	globals(Globals::app_paused) = paused;
    	return paused;
    }
};


#endif /* COMMANDS_PAUSE_COMMAND_H_ */
