/*
 * remove_entity_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_REMOVE_ENTITY_COMMAND_H_
#define COMMANDS_REMOVE_ENTITY_COMMAND_H_

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class RemoveEntityCommand
{
public:
    RemoveEntityCommand() {}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	entity_system.remove_entity(entity_system.previous_entity_id());
    }
};


#endif /* COMMANDS_REMOVE_ENTITY_COMMAND_H_ */
