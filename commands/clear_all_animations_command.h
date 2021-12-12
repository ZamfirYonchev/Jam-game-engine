/*
 * clear_all_animations_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_ALL_ANIMATIONS_COMMAND_H_
#define COMMANDS_CLEAR_ALL_ANIMATIONS_COMMAND_H_

#include "../command_value.h"

template<typename ResourceSystemT>
class ClearAllAnimationsCommand
{
public:
	ResourceSystemT& resource_system;

	ClearAllAnimationsCommand(ResourceSystemT& _resource_system) : resource_system{_resource_system} {}

    CommandValue operator()() const
	{
		resource_system.clear_animations();
		return CommandValue{0.0};
	}
};

#endif /* COMMANDS_CLEAR_ALL_ANIMATIONS_COMMAND_H_ */
