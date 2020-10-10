/*
 * control_system.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "control_system.h"
#include "../components/control.h"
#include "../components/health.h"
#include "../commands/call_procedure_command.h"
#include "../commands/modify_position_command.h"
#include "../commands/modify_control_command.h"
#include <algorithm>
#include "systems.h"
#include "entity_system.h"
#include "command_system.h"

void ControlSystem::update(const Time time_diff)
{
	for(const auto id : entities)
	{
		auto& control = system<EntitySystem>().entity_component<Control>(id);
    	if(control)
    	{
			const auto& health = system<EntitySystem>().entity_component<Health>(id);

			if(health.alive())
			{
				control.update_decisions(time_diff);
				if(health.stunned())
				{
					control.set_decision_walk(0.5*control.decision_walk());
					control.set_decision_jump(0.5*control.decision_jump());
					control.set_decision_duck(0.5*control.decision_duck());
				}
			}
			else
				control.clear_decisions();


			if(control.decision_attack() && control.attack_proc_id() >= 0)
			{
				const auto& position = system<EntitySystem>().entity_component<Position>(id);
				system<CommandSystem>().push(std::make_unique<CallProcedureCommand>(control.attack_proc_id()));
				if(control.look_dir() == Control::LEFT)
				{
					system<CommandSystem>().push(std::make_unique<ModifyPositionCommand>(position.x(), position.y(), 0, 0));
					system<CommandSystem>().push(std::make_unique<ModifyControlCommand>(0, 0, 0, -0.0, -0.0));
					system<CommandSystem>().push(std::make_unique<ModifyControlCommand>(0, 0, 0, -1, control.look_dir()));
				}
				else // Look dir is right
				{
					//command_queue().push(new ModifyPositionCommand(-0.0, 0, 0, 0));
					//command_queue().push(new ModifyPositionCommand(position->x()+position->w(), position->y(), 0, 0));
					system<CommandSystem>().push(std::make_unique<ModifyPositionCommand>(position.x(), position.y(), 0, 0));
					system<CommandSystem>().push(std::make_unique<ModifyControlCommand>(0, 0, 0, -0.0, -0.0));
					system<CommandSystem>().push(std::make_unique<ModifyControlCommand>(0, 0, 0, 1, control.look_dir()));
				}
			}
    	}
    	else
    	{
    		//error *it
    	}
	}
}
