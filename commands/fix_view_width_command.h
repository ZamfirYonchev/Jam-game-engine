/*
 * fix_view_width_command.h
 *
 *  Created on: May 23, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_FIX_VIEW_WIDTH_COMMAND_H_
#define COMMANDS_FIX_VIEW_WIDTH_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../utilities.h"

template<typename EntitySystemT, typename CommandSystemT>
class FixViewWidthCommand
{
public:
	EntitySystemT& entity_system;
	CommandSystemT& command_system;
	Globals& globals;

	FixViewWidthCommand(EntitySystemT& _entity_system, CommandSystemT& _command_system, Globals& _globals)
	: entity_system{_entity_system}
	, command_system{_command_system}
	, globals{_globals}
	{}

    CommandValue operator()() const
	{
		Position& position = entity_system.template entity_component<Position>(EntityID{0});
		position.set_w(int(position.h()*globals(Globals::app_resolution_x).real()/globals(Globals::app_resolution_y).real()));

    	return CommandValue{0.0};
	}
};



#endif /* COMMANDS_FIX_VIEW_WIDTH_COMMAND_H_ */
