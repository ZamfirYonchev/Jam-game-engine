/*
 * clear_all_entities_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_ALL_ENTITIES_COMMAND_H_
#define COMMANDS_CLEAR_ALL_ENTITIES_COMMAND_H_

#include "../command_value.h"

template<typename EntitySystemT, typename AllSystemsT>
class ClearAllEntitiesCommand
{
public:
	EntitySystemT& entity_system;
	AllSystemsT& all_systems;

	ClearAllEntitiesCommand(EntitySystemT& _entity_system, AllSystemsT& _all_systems)
	: entity_system{_entity_system}
	, all_systems{_all_systems}
	{}

    CommandValue operator()() const
	{
    	all_systems.clear();
		entity_system.clear();
		return CommandValue{0.0};
	}
};


#endif /* COMMANDS_CLEAR_ALL_ENTITIES_COMMAND_H_ */
