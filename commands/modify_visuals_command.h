/*
 * modify_visuals_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_VISUALS_COMMAND_H_
#define COMMANDS_MODIFY_VISUALS_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../math_ext.h"
#include "../systems/rendering_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class ModifyVisualsCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto repeat_x = command_system.exec_next();
    	const auto repeat_y = command_system.exec_next();
    	const auto layer = command_system.exec_next();

    	const EntityID selected_entity = globals(Globals::selected_entity).integer();
    	Visuals& visuals = entity_system.entity_component(selected_entity, Visuals::null);

		if(visuals)
		{
			if(is_negative_zero(repeat_x.real()))
				visuals.set_repeat_x(0);
			else
				visuals.set_repeat_x(visuals.repeat_x()+repeat_x.integer());

			if(is_negative_zero(repeat_y.real()))
				visuals.set_repeat_y(0);
			else
				visuals.set_repeat_y(visuals.repeat_y()+repeat_y.integer());

			if(is_negative_zero(layer.real()))
			{
				if(visuals.layer() != Visuals::VisualLayer::FAR_BACKGROUND)
				{
					visuals.set_layer(Visuals::VisualLayer(0));
					rendering_system.component_updated(visuals, selected_entity, false);
				}
			}
			else
			{
				if(layer.integer() != 0)
				{
					visuals.set_layer(Visuals::VisualLayer(int(visuals.layer())+layer.integer()));
					rendering_system.component_updated(visuals, selected_entity, false);
				}
			}

			return CommandReturnValue{0l};
		}
		else
		{
			//error selected_entity
			return CommandReturnValue{-1l};
		}
	}
};


#endif /* COMMANDS_MODIFY_VISUALS_COMMAND_H_ */
