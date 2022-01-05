/*
 * modify_visuals_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_VISUALS_COMMAND_H_
#define COMMANDS_MODIFY_VISUALS_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../math_ext.h"

template<typename CommandSystemT, typename EntitySystemT, typename RenderingSystemT, typename VisualsT>
class ModifyVisualsCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;
	RenderingSystemT& rendering_system;
	Globals& globals;

	ModifyVisualsCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system, RenderingSystemT& _rendering_system, Globals& _globals)
	: command_system{_command_system}
	, entity_system{_entity_system}
	, rendering_system{_rendering_system}
	, globals{_globals}
	{}

	CommandValue operator()() const
	{
    	const auto repeat_x = command_system.exec_next();
    	const auto repeat_y = command_system.exec_next();
    	const auto layer = command_system.exec_next();

    	const EntityID selected_entity = globals(Globals::selected_entity).integer();
    	auto& visuals = entity_system.template entity_component<VisualsT>(selected_entity);

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
				if(visuals.layer() != VisualLayer::FAR_BACKGROUND)
				{
					visuals.set_layer(VisualLayer(0));
					rendering_system.component_updated(visuals, selected_entity, 0);
				}
			}
			else
			{
				if(layer.integer() != 0)
				{
					visuals.set_layer(VisualLayer(int(visuals.layer())+layer.integer()));
					rendering_system.component_updated(visuals, selected_entity, 0);
				}
			}

			return globals(Globals::selected_entity);
		}
		else
		{
			//error selected_entity
			return CommandValue{-1};
		}
	}
};


#endif /* COMMANDS_MODIFY_VISUALS_COMMAND_H_ */
