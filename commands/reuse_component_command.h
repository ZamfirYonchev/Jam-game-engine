/*
 * reuse_component_command.h
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_REUSE_COMPONENT_COMMAND_H_
#define COMMANDS_REUSE_COMPONENT_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../types.h"
#include <sstream>

class ResourceSystem;
class InputSystem;
class RenderingSystem;

template<typename T>
class ReuseComponentCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto source_id = command_system.exec_next();

    	const T& component = entity_system.entity_component(source_id.integer(), T::null);
		std::stringstream ss;
		ss << component;
		command_system.process_stream(ss);

    	return CommandReturnValue{0l};
	}
};

#endif /* COMMANDS_REUSE_COMPONENT_COMMAND_H_ */
