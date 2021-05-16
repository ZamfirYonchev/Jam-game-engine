/*
 * fix_view_width_command.h
 *
 *  Created on: May 23, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_FIX_VIEW_WIDTH_COMMAND_H_
#define COMMANDS_FIX_VIEW_WIDTH_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../utilities.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class FixViewWidthCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		Position& position = entity_system.template entity_component<Position>(EntityID{0});
		position.set_w(int(position.h()*globals(Globals::app_resolution_x).real()/globals(Globals::app_resolution_y).real()));

    	return CommandReturnValue{0.0};
	}
};



#endif /* COMMANDS_FIX_VIEW_WIDTH_COMMAND_H_ */
