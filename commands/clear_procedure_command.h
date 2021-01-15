/*
 * clear_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_PROCEDURE_COMMAND_H_
#define COMMANDS_CLEAR_PROCEDURE_COMMAND_H_

#include "command_return_value.h"
#include "../types.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ClearProcedureCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto proc_id = command_system.exec_next();
    	command_system.procedure(ProcedureID(proc_id.integer())).clear();
    	return CommandReturnValue{0.0};
    }
};


#endif /* COMMANDS_CLEAR_PROCEDURE_COMMAND_H_ */
