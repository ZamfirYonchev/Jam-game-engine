/*
 * select_entity_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_SELECT_ENTITY_COMMAND_H_
#define COMMANDS_SELECT_ENTITY_COMMAND_H_

#include "../types.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class SelectEntityCommand
{
public:
	SelectEntityCommand(const EntityID id)
	: m_id(id)
	{}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		//entity_system.add_accessed_entity(entity_system.resolved_id(m_id));
		entity_system.add_accessed_entity(m_id);
	}

private:
    EntityID m_id;
};

#endif /* COMMANDS_SELECT_ENTITY_COMMAND_H_ */
