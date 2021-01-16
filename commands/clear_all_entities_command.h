/*
 * clear_all_entities_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_ALL_ENTITIES_COMMAND_H_
#define COMMANDS_CLEAR_ALL_ENTITIES_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class ClearAllEntitiesCommand
{
public:
	ClearAllEntitiesCommand() {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	all_systems.clear();
		entity_system.clear();
		return 0.0;
	}
};


#endif /* COMMANDS_CLEAR_ALL_ENTITIES_COMMAND_H_ */
