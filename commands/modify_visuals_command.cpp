/*
 * modify_visuals_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_visuals_command.h"
#include "../math_ext.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"
#include "../systems/rendering_system.h"

void ModifyVisualsCommand::execute() const
{
	auto& visuals = system<EntitySystem>().entity_component<Visuals>(system<EntitySystem>().previous_entity_id());
	if(visuals)
	{
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
				system<RenderingSystem>().remove_id(system<EntitySystem>().previous_entity_id());
				visuals.set_layer(Visuals::VisualLayer(0));
				system<RenderingSystem>().add_id(system<EntitySystem>().previous_entity_id());
			}
		}
		else
		{
			if(m_layer != 0)
			{
				system<RenderingSystem>().remove_id(system<EntitySystem>().previous_entity_id());
				visuals.set_layer(Visuals::VisualLayer(visuals.layer()+int(m_layer)));
				system<RenderingSystem>().add_id(system<EntitySystem>().previous_entity_id());
			}
		}
	}
	else
	{
		//error system<EntitySystem>().previous_entity()
	}
}
