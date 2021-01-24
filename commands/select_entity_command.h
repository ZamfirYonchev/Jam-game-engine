/*
 * select_entity_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_SELECT_ENTITY_COMMAND_H_
#define COMMANDS_SELECT_ENTITY_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../types.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class SelectEntityCommand
{
public:
	SelectEntityCommand(const EntityID entity_id) : m_entity_id{entity_id, 0} {} // @suppress("Symbol is not resolved")
	SelectEntityCommand() : m_entity_id{-1.0} {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto entity_id = (m_entity_id.integer() >= 0) ? m_entity_id : command_system.exec_next();
    	globals(Globals::selected_entity) = entity_id;
		return entity_id;
	}

	const CommandReturnValue m_entity_id;
};

#endif /* COMMANDS_SELECT_ENTITY_COMMAND_H_ */
