/*
 * remove_entity_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_REMOVE_ENTITY_COMMAND_H_
#define COMMANDS_REMOVE_ENTITY_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"

template<typename EntitySystemT>
class RemoveEntityCommand
{
public:
	EntitySystemT& entity_system;
	Globals& globals;

	RemoveEntityCommand(EntitySystemT& _entity_system, Globals& _globals)
	: entity_system{_entity_system}
	, globals{_globals}
	{}

	CommandValue operator()() const
    {
    	const EntityID selected_entity = globals(Globals::selected_entity).integer();
    	entity_system.remove_entity(selected_entity);
		return CommandValue{0.0};
    }
};

#endif /* COMMANDS_REMOVE_ENTITY_COMMAND_H_ */
