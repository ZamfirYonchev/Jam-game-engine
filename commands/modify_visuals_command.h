/*
 * modify_visuals_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_VISUALS_COMMAND_H_
#define COMMANDS_MODIFY_VISUALS_COMMAND_H_

#include "command_return_value.h"
#include "../math_ext.h"
#include "../systems/rendering_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ModifyVisualsCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto repeat_x = command_system.exec_next();
    	const auto repeat_y = command_system.exec_next();
    	const auto spr_id = command_system.exec_next();
    	const auto layer = command_system.exec_next();

    	Visuals& visuals = entity_system.entity_component(entity_system.previous_entity_id(), (Visuals*)nullptr);

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

			if(is_negative_zero(spr_id.real()))
				visuals.set_spritesheet_id(SpritesheetID{0});
			else
				visuals.set_spritesheet_id(SpritesheetID(visuals.spritesheet_id()+ spr_id.integer()));

			if(is_negative_zero(layer.real()))
			{
				if(visuals.layer() != Visuals::VisualLayer::FAR_BACKGROUND)
				{
					visuals.set_layer(Visuals::VisualLayer(0));
					rendering_system.component_updated(visuals, entity_system.previous_entity_id(), false);
				}
			}
			else
			{
				if(layer.integer() != 0)
				{
					visuals.set_layer(Visuals::VisualLayer(int(visuals.layer())+layer.integer()));
					rendering_system.component_updated(visuals, entity_system.previous_entity_id(), false);
				}
			}

			return 0.0;
		}
		else
		{
			//error entity_system.previous_entity()
			return -1.0;
		}
	}
};


#endif /* COMMANDS_MODIFY_VISUALS_COMMAND_H_ */
