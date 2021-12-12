/*
 * select_entity_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_SELECT_ENTITY_COMMAND_H_
#define COMMANDS_SELECT_ENTITY_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../types.h"

template<typename CommandSystemT>
class SelectEntityCommand
{
public:
	CommandSystemT& command_system;
	Globals& globals;
	const CommandValue m_entity_id;

	SelectEntityCommand(CommandSystemT& _command_system, Globals& _globals, const EntityID entity_id)
	: command_system{_command_system}
	, globals{_globals}
	, m_entity_id{entity_id, 0}
	{}

	SelectEntityCommand(CommandSystemT& _command_system, Globals& _globals)
	: command_system{_command_system}
	, globals{_globals}
	, m_entity_id{-1.0} {}

    CommandValue operator()() const
	{
    	const auto entity_id = (m_entity_id.integer() >= 0) ? m_entity_id : command_system.exec_next();
    	globals(Globals::selected_entity) = entity_id;
		return entity_id;
	}
};

#endif /* COMMANDS_SELECT_ENTITY_COMMAND_H_ */
