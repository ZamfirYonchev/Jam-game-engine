/*
 * add_procedure_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_PROCEDURE_COMMAND_H_
#define COMMANDS_ADD_PROCEDURE_COMMAND_H_

#include "extend_procedure_command.h"
#include "../systems/resource_system.h"
#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class AddProcedureCommand
{
public:
    AddProcedureCommand(int num_of_cmds) : m_num_of_cmds(num_of_cmds) {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	command_system.addNewProcedure();
        globals.access_procedure_id = command_system.last_procedure_id();

        if(m_num_of_cmds > 0)
        {
            ExtendProcedureCommand(globals.access_procedure_id, m_num_of_cmds)(entity_system, resource_system, input_system, command_system, rendering_system, all_systems, globals);
        }
    }

private:
    int m_num_of_cmds;
};


#endif /* COMMANDS_ADD_PROCEDURE_COMMAND_H_ */
