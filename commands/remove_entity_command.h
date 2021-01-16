/*
 * remove_entity_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_REMOVE_ENTITY_COMMAND_H_
#define COMMANDS_REMOVE_ENTITY_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class RemoveEntityCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const EntityID selected_entity = globals(Globals::selected_entity).integer();
    	entity_system.remove_entity(selected_entity);
		return CommandReturnValue{0l};
    }
};


#endif /* COMMANDS_REMOVE_ENTITY_COMMAND_H_ */
