/*
 * extend_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_EXTEND_PROCEDURE_COMMAND_H_
#define COMMANDS_EXTEND_PROCEDURE_COMMAND_H_

#include "command_return_value.h"
#include "../types.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ExtendProcedureCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	const auto proc_id = command_system.exec_next();
    	const auto num_of_cmds = command_system.exec_next();

    	auto& proc = command_system.procedure(ProcedureID(proc_id.integer()));

		for(int i = 0; i < num_of_cmds.integer(); ++i)
		{
			proc.add_command(command_system.pop_next());
		}

		return proc_id;
    }
};

#endif /* COMMANDS_EXTEND_PROCEDURE_COMMAND_H_ */
