/*
 * clear_all_procedures_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_
#define COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ClearAllProceduresCommand
{
public:
    ClearAllProceduresCommand() {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	command_system.clear_procedures();
		return 0.0;
    }
};

#endif /* COMMANDS_CLEAR_ALL_PROCEDURES_COMMAND_H_ */
