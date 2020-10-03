/*
 * modify_visuals_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_visuals_command.h"
#include "../globals.h"
#include "../math_ext.h"

void ModifyVisualsCommand::execute() const
{
	if(entity_system().previous_entity())
	{
		auto& visuals = entity_system().previous_entity()->component<Visuals>();

		if(is_negative_zero(m_render_state))
			visuals.set_new_state(Visuals::IDLE);
		else
			visuals.set_new_state(Visuals::RenderStates((visuals.state() + int(m_render_state))%6));

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
			if(visuals.layer() != 0)
			{
				rendering_system().remove_id(entity_system().previous_entity()->id());
				visuals.set_layer(Visuals::VisualLayer(0));
				rendering_system().add_id(entity_system().previous_entity()->id());
			}
		}
		else
		{
			if(m_layer != 0)
			{
				rendering_system().remove_id(entity_system().previous_entity()->id());
				visuals.set_layer(Visuals::VisualLayer(visuals.layer()+int(m_layer)));
				rendering_system().add_id(entity_system().previous_entity()->id());
			}
		}
	}
	else
	{
		//error entity_system().previous_entity()
	}
}
