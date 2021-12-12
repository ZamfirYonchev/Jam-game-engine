/*
 * add_animation_command.h
 *
 *  Created on: Jan 17, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_ANIMATION_COMMAND_H_
#define COMMANDS_ADD_ANIMATION_COMMAND_H_

#include "../command_value.h"

template<typename CommandSystemT, typename ResourceSystemT>
class AddAnimationCommand
{
public:
	CommandSystemT& command_system;
	ResourceSystemT& resource_system;

	AddAnimationCommand(CommandSystemT& _command_system, ResourceSystemT& _resource_system)
	: command_system{_command_system}
	, resource_system{_resource_system}
	{}

    CommandValue operator()() const
    {
    	const auto frame_delay_ms = command_system.exec_next();
    	const auto scale_factor = command_system.exec_next();
    	return CommandValue{resource_system.addNewAnimation({frame_delay_ms.integer(), scale_factor.real()}), 0};
    }
};

#endif /* COMMANDS_ADD_ANIMATION_COMMAND_H_ */
