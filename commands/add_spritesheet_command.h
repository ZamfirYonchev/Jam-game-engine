/*
 * add_spritesheet_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_SPRITESHEET_COMMAND_H_
#define COMMANDS_ADD_SPRITESHEET_COMMAND_H_

#include "../spritesheet.h"
#include "../systems/resource_system.h"
#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class AddSpritesheetCommand
{
public:
    AddSpritesheetCommand(const Spritesheet& spritesheet) : m_spritesheet(spritesheet) {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	resource_system.addNewSpritesheet(m_spritesheet);
        globals.access_spritesheet_id = resource_system.last_spritesheet_id();
    }

private:
    Spritesheet m_spritesheet;
};

#endif /* COMMANDS_ADD_SPRITESHEET_COMMAND_H_ */
