/*
 * command_value_extractor.h
 *
 *  Created on: Dec 12, 2021
 *      Author: zamfi
 */

#ifndef COMMAND_VALUE_EXTRACTOR_H_
#define COMMAND_VALUE_EXTRACTOR_H_

#include "command_value.h"

template<typename CommandSystemT>
struct CommandValueExtractor
{
	CommandValueExtractor(CommandSystemT& _command_system)
	: command_system{_command_system}
	{}

	CommandValue operator()()
	{
		return command_system.get().exec_next();
	}

	std::reference_wrapper<CommandSystemT> command_system;
};

#endif /* COMMAND_VALUE_EXTRACTOR_H_ */
