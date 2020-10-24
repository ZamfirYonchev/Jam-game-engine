/*
 * finalize_build_command.h
 *
 *  Created on: Oct 24, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_FINALIZE_BUILD_COMMAND_H_
#define COMMANDS_FINALIZE_BUILD_COMMAND_H_

#include "../types.h"
#include "../components/absolute_position.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class FinalizeBuildCommand
{
public:
	FinalizeBuildCommand() {}
	FinalizeBuildCommand(const FinalizeBuildCommand& val) = default;
	FinalizeBuildCommand(FinalizeBuildCommand&& val) noexcept = default;
	FinalizeBuildCommand(FinalizeBuildCommand& val) = default;

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		const auto& position = entity_system.entity_component(entity_system.previous_entity_id(), (Position*)nullptr);
		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, AbsolutePosition{position.x(), position.y(), position.w(), position.h()});
	}
};

#endif /* COMMANDS_FINALIZE_BUILD_COMMAND_H_ */
