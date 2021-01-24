/*
 * add_entity_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_ENTITY_COMMAND_H_
#define COMMANDS_ADD_ENTITY_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class AddEntityCommand
{
public:
    AddEntityCommand() {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const EntityID entity_id = entity_system.add_new_entity();
    	globals(Globals::selected_entity) = CommandReturnValue{entity_id, 0};
    	return CommandReturnValue{entity_id, 0};
    }
};


#endif /* COMMANDS_ADD_ENTITY_COMMAND_H_ */
