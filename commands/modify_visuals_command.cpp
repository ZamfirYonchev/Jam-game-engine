/*
 * modify_visuals_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_visuals_command.h"
#include "../globals.h"
#include <cmath>

void ModifyVisualsCommand::execute() const
{
	if(globals.entity_system.entity(globals.access_entity_id))
	{
		Visuals* visuals = globals.entity_system.entity(globals.access_entity_id)->visuals();

		if(m_render_state == 0 && std::signbit(m_render_state))
			visuals->set_new_state(Visuals::IDLE);
		else
			visuals->set_new_state(Visuals::RenderStates((globals.entity_system.entity(globals.access_entity_id)->visuals()->state() + int(m_render_state))%6));

		if(m_repeat_x == 0 && std::signbit(m_repeat_x))
			visuals->set_repeat_x(0);
		else
			visuals->set_repeat_x(globals.entity_system.entity(globals.access_entity_id)->visuals()->repeat_x()+int(m_repeat_x));

		if(m_repeat_y == 0 && std::signbit(m_repeat_y))
			visuals->set_repeat_y(0);
		else
			visuals->set_repeat_y(globals.entity_system.entity(globals.access_entity_id)->visuals()->repeat_y()+int(m_repeat_y));

		if(m_spr_id == 0 && std::signbit(m_spr_id))
			visuals->set_spritesheet_id(0);
		else
			visuals->set_spritesheet_id(globals.entity_system.entity(globals.access_entity_id)->visuals()->spritesheet_id()+int(m_spr_id));

		if(m_layer == 0 && std::signbit(m_layer))
		{
			if(visuals->layer() != 0)
			{
				globals.rendering_system.remove_id(globals.access_entity_id);
				visuals->set_layer(Visuals::VisualLayer(0));
				globals.rendering_system.add_id(globals.access_entity_id);
			}
		}
		else
		{
			if(m_layer != 0)
			{
				globals.rendering_system.remove_id(globals.access_entity_id);
				visuals->set_layer(Visuals::VisualLayer(visuals->layer()+int(m_layer)));
				globals.rendering_system.add_id(globals.access_entity_id);
			}
		}
	}
	else
	{
		//error globals.access_entity_id
	}
}
