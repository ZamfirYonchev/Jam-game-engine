/*
 * fix_view_width_command.h
 *
 *  Created on: May 23, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_FIX_VIEW_WIDTH_COMMAND_H_
#define COMMANDS_FIX_VIEW_WIDTH_COMMAND_H_

#include <string>
#include "../globals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class FixViewWidthCommand
{
public:
	FixViewWidthCommand() = default;

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		Position& position = entity_system.entity_component(AbsEntityID{0}, (Position*)nullptr);
		position.set_w(int(position.h()*globals.resolution_x/globals.resolution_y));
	}

private:
};



#endif /* COMMANDS_FIX_VIEW_WIDTH_COMMAND_H_ */
