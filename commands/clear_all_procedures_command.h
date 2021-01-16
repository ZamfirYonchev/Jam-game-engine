/*
 * clear_all_procedures_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_
#define COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class ClearAllProceduresCommand
{
public:
    ClearAllProceduresCommand() {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	command_system.clear_procedures();
    	return CommandReturnValue{0l};
    }
};

#endif /* COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_ */
