/*
 * add_entity_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_ENTITY_COMMAND_H_
#define COMMANDS_ADD_ENTITY_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"

template<typename EntitySystemT>
class AddEntityCommand
{
public:
	EntitySystemT& entity_system;
	Globals& globals;

	AddEntityCommand(EntitySystemT& _entity_system, Globals& _globals)
	: entity_system{_entity_system}
	, globals{_globals}
	{}

	CommandValue operator()() const
    {
    	const EntityID entity_id = entity_system.add_new_entity();
    	globals(Globals::selected_entity) = CommandValue{entity_id, 0};
    	return CommandValue{entity_id, 0};
    }
};


#endif /* COMMANDS_ADD_ENTITY_COMMAND_H_ */
