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
#include "../command_queue.h"
#include "entity_system.h"
#include "systems.h"

void ControlSystem::update(const Time time_diff)
{
	std::for_each(cbegin(entities), cend(entities),
	[time_diff](const EntityID id)
	{
    	if(system<EntitySystem>().entity(id))
    	{
			Entity& entity = *(system<EntitySystem>().entity(id));
			auto& control = entity.component<Control>();
			const auto& health = entity.component<Health>();


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
				const auto& position = entity.component<Position>();
				system<CommandQueue>().push(std::make_unique<CallProcedureCommand>(control.attack_proc_id()));
				if(control.look_dir() == Control::LEFT)
				{
					system<CommandQueue>().push(std::make_unique<ModifyPositionCommand>(position.x(), position.y(), 0, 0));
					system<CommandQueue>().push(std::make_unique<ModifyControlCommand>(0, 0, 0, -0.0, -0.0));
					system<CommandQueue>().push(std::make_unique<ModifyControlCommand>(0, 0, 0, -1, control.look_dir()));
				}
				else // Look dir is right
				{
					//command_queue().push(new ModifyPositionCommand(-0.0, 0, 0, 0));
					//command_queue().push(new ModifyPositionCommand(position->x()+position->w(), position->y(), 0, 0));
					system<CommandQueue>().push(std::make_unique<ModifyPositionCommand>(position.x(), position.y(), 0, 0));
					system<CommandQueue>().push(std::make_unique<ModifyControlCommand>(0, 0, 0, -0.0, -0.0));
					system<CommandQueue>().push(std::make_unique<ModifyControlCommand>(0, 0, 0, 1, control.look_dir()));
				}
			}
    	}
    	else
    	{
    		//error *it
    	}
	});
}
