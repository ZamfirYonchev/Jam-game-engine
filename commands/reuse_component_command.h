/*
 * reuse_component_command.h
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_REUSE_COMPONENT_COMMAND_H_
#define COMMANDS_REUSE_COMPONENT_COMMAND_H_

#include "../command_value.h"
#include "../types.h"
#include <sstream>

template<typename ComponentT, typename CommandSystemT, typename EntitySystemT>
class ReuseComponentCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;

	ReuseComponentCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system)
	: command_system{_command_system}
	, entity_system{_entity_system}
	{}

    CommandValue operator()() const
	{
    	const auto source_id = command_system.exec_next();

    	const ComponentT& component = entity_system.template entity_component<ComponentT>(source_id.integer());
    	//TODO use set_entity_component instead
		std::stringstream ss;
		ss << component;
		command_system.parse(ss);

    	return CommandValue{0.0};
	}
};

#endif /* COMMANDS_REUSE_COMPONENT_COMMAND_H_ */
