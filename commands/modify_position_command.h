/*
 * modify_position_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_POSITION_COMMAND_H_
#define COMMANDS_MODIFY_POSITION_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../math_ext.h"
#include "../components/position.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class ModifyPositionCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto x = command_system.exec_next();
    	const auto y = command_system.exec_next();
    	const auto w = command_system.exec_next();
    	const auto h = command_system.exec_next();

    	const EntityID selected_entity = globals(Globals::selected_entity).integer();
    	Position& position = entity_system.entity_component(selected_entity, Position::null);

		if(position)
		{
			if(is_negative_zero(x.real()))
				position.set_x(0.0);
			else
				position.mod_x(x.real());

			if(is_negative_zero(y.real()))
				position.set_y(0.0);
			else
				position.mod_y(y.real());

			if(is_negative_zero(w.real()))
				position.set_w(0.0);
			else
				position.mod_w(w.real());

			if(is_negative_zero(h.real()))
				position.set_h(0.0);
			else
				position.mod_h(h.real());

			return CommandReturnValue{0.0};
		}
		else
		{
			//error selected_entity
			return CommandReturnValue{-1.0};
		}
	}
};


#endif /* COMMANDS_MODIFY_POSITION_COMMAND_H_ */
