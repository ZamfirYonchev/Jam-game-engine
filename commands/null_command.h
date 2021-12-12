/*
 * null_command.h
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_NULL_COMMAND_H_
#define COMMANDS_NULL_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"

class NullCommand
{
public:

    CommandValue operator()() const
    {
    	return CommandValue{0.0};
    }
};

#endif /* COMMANDS_NULL_COMMAND_H_ */
