/*
 * select_entity_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_SELECT_ENTITY_COMMAND_H_
#define COMMANDS_SELECT_ENTITY_COMMAND_H_

#include "command_return_value.h"
#include "../types.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class SelectEntityCommand
{
public:
	SelectEntityCommand(const EntityID entity_id) : m_entity_id{static_cast<int64_t>(entity_id)} {}
	SelectEntityCommand() : m_entity_id{static_cast<int64_t>(-1)} {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto entity_id = (m_entity_id.integer() >= 0) ? m_entity_id : command_system.exec_next();
		entity_system.add_accessed_entity(entity_id.integer());

		return entity_id;
	}

	const CommandReturnValue m_entity_id;
};

#endif /* COMMANDS_SELECT_ENTITY_COMMAND_H_ */
