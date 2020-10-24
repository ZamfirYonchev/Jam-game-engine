/*
 * quit_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_QUIT_COMMAND_H_
#define COMMANDS_QUIT_COMMAND_H_

#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class QuitCommand
{
public:
    QuitCommand() {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
        globals.app_running = false;
    }
};


#endif /* COMMANDS_QUIT_COMMAND_H_ */
