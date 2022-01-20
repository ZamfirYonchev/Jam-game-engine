/*
 * add_animation_command.h
 *
 *  Created on: Jan 17, 2021
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_ANIMATION_COMMAND_H_
#define COMMANDS_ADD_ANIMATION_COMMAND_H_

#include "../command_value.h"
#include "../animation.h"

template<typename CommandSystemT, typename AnimationResourceSystemT>
class AddAnimationCommand
{
public:
	CommandSystemT& command_system;
	AnimationResourceSystemT& animations;

	AddAnimationCommand(CommandSystemT& _command_system, AnimationResourceSystemT& _animations)
	: command_system{_command_system}
	, animations{_animations}
	{}

    CommandValue operator()() const
    {
    	const Time frame_delay_ms = command_system.exec_next();
    	const double scale_factor = command_system.exec_next();
    	return CommandValue{animations.add_new(Animation{frame_delay_ms, scale_factor})};
    }
};

#endif /* COMMANDS_ADD_ANIMATION_COMMAND_H_ */
