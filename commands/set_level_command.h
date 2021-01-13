/*
 * set_level_command.h
 *
 *  Created on: Dec 9, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_SET_LEVEL_COMMAND_H_
#define COMMANDS_SET_LEVEL_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class SetLevelCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto level_name = command_system.exec_next();
		globals.level_name = level_name.string();

		return 0.0;
	}

private:
};




#endif /* COMMANDS_SET_LEVEL_COMMAND_H_ */
