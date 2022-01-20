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

template<typename EntitySystemT, typename CommandSystemT, typename PositionT>
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
		auto& position = entity_system.template entity_component<PositionT>(EntityID{0});
		const int new_width = position.h()*globals(Globals::app_resolution_x).integer()/globals(Globals::app_resolution_y).integer();
		position.set_w(new_width);

    	return CommandValue{new_width};
	}
};



#endif /* COMMANDS_FIX_VIEW_WIDTH_COMMAND_H_ */
