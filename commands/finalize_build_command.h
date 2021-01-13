/*
 * finalize_build_command.h
 *
 *  Created on: Oct 24, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_FINALIZE_BUILD_COMMAND_H_
#define COMMANDS_FINALIZE_BUILD_COMMAND_H_

#include "command_return_value.h"
#include "../types.h"
#include "../components/absolute_position.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class FinalizeBuildCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		const auto& position = entity_system.entity_component(entity_system.previous_entity_id(), (Position*)nullptr);
		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, AbsolutePosition{position.x(), position.y(), position.w(), position.h()});
		return 0.0;
	}
};

#endif /* COMMANDS_FINALIZE_BUILD_COMMAND_H_ */
