/*
 * reuse_component_command.h
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_REUSE_COMPONENT_COMMAND_H_
#define COMMANDS_REUSE_COMPONENT_COMMAND_H_

#include "../types.h"
#include <sstream>

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

template<typename T>
class ReuseComponentCommand
{
public:
	ReuseComponentCommand(const EntityID& source_id)
	: m_source_id(source_id)
	{}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		const T& component = entity_system.entity_component(entity_system.resolved_id(m_source_id), (T*)nullptr);
		std::stringstream ss;
		ss << component;
		command_system.process_stream(ss);
	}

private:
    EntityID m_source_id;
};

#endif /* COMMANDS_REUSE_COMPONENT_COMMAND_H_ */
