/*
 * modify_visuals_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_VISUALS_COMMAND_H_
#define COMMANDS_MODIFY_VISUALS_COMMAND_H_

#include "../math_ext.h"
#include "../systems/rendering_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ModifyVisualsCommand
{
public:
	ModifyVisualsCommand(double render_state, double repeat_x, double repeat_y, double spr_id, double layer)
	: m_render_state(render_state)
	, m_repeat_x(repeat_x)
	, m_repeat_y(repeat_y)
	, m_spr_id(spr_id)
	, m_layer(layer)
	{}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	Visuals& visuals = entity_system.entity_component(entity_system.previous_entity_id(), (Visuals*)nullptr);

		if(visuals)
		{
			if(is_negative_zero(m_render_state))
				visuals.set_new_state(Visuals::RenderStates::IDLE);
			else
				visuals.set_new_state(Visuals::RenderStates((int(visuals.state()) + int(m_render_state))%6));

			if(is_negative_zero(m_repeat_x))
				visuals.set_repeat_x(0);
			else
				visuals.set_repeat_x(visuals.repeat_x()+int(m_repeat_x));

			if(is_negative_zero(m_repeat_y))
				visuals.set_repeat_y(0);
			else
				visuals.set_repeat_y(visuals.repeat_y()+int(m_repeat_y));

			if(is_negative_zero(m_spr_id))
				visuals.set_spritesheet_id(SpritesheetID{0});
			else
				visuals.set_spritesheet_id(SpritesheetID{visuals.spritesheet_id()+int(m_spr_id)});

			if(is_negative_zero(m_layer))
			{
				if(visuals.layer() != Visuals::VisualLayer::FAR_BACKGROUND)
				{
					visuals.set_layer(Visuals::VisualLayer(0));
					rendering_system.component_updated(visuals, entity_system.previous_entity_id(), false);
				}
			}
			else
			{
				if(m_layer != 0)
				{
					visuals.set_layer(Visuals::VisualLayer(int(visuals.layer())+int(m_layer)));
					rendering_system.component_updated(visuals, entity_system.previous_entity_id(), false);
				}
			}
		}
		else
		{
			//error entity_system.previous_entity()
		}
	}

private:
	double m_render_state, m_repeat_x, m_repeat_y, m_spr_id, m_layer;
};


#endif /* COMMANDS_MODIFY_VISUALS_COMMAND_H_ */
