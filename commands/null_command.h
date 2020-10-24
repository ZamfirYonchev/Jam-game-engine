/*
 * null_command.h
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_NULL_COMMAND_H_
#define COMMANDS_NULL_COMMAND_H_

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class NullCommand
{
public:

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {}
};

#endif /* COMMANDS_NULL_COMMAND_H_ */
