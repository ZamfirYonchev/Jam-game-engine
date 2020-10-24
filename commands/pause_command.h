/*
 * pause_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_PAUSE_COMMAND_H_
#define COMMANDS_PAUSE_COMMAND_H_

#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class PauseCommand
{
public:
    PauseCommand(bool paused) : m_paused(paused) {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
        globals.app_paused = m_paused;
    }

private:
    bool m_paused;
};


#endif /* COMMANDS_PAUSE_COMMAND_H_ */
