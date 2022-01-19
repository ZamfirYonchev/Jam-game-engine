/*
 * clear_all_animations_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_ALL_ANIMATIONS_COMMAND_H_
#define COMMANDS_CLEAR_ALL_ANIMATIONS_COMMAND_H_

#include "../command_value.h"

template<typename AnimationResourceSystemT>
class ClearAllAnimationsCommand
{
public:
	AnimationResourceSystemT& animations;

	ClearAllAnimationsCommand(AnimationResourceSystemT& _animations)
	: animations{_animations}
	{}

    CommandValue operator()() const
	{
    	animations.clear();
		return CommandValue{0};
	}
};

#endif /* COMMANDS_CLEAR_ALL_ANIMATIONS_COMMAND_H_ */
