/*
 * finalize_build_command.h
 *
 *  Created on: Oct 24, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_FINALIZE_BUILD_COMMAND_H_
#define COMMANDS_FINALIZE_BUILD_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../types.h"
#include "../components/absolute_position.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class FinalizeBuildCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const EntityID selected_entity = globals(Globals::selected_entity).integer();
		const auto& position = entity_system.entity_component(selected_entity, Position::null);
		entity_system.set_entity_component(selected_entity, all_systems, rendering_system, AbsolutePosition{position.x(), position.y(), position.w(), position.h()});
    	return CommandReturnValue{0.0};
	}
};

#endif /* COMMANDS_FINALIZE_BUILD_COMMAND_H_ */
