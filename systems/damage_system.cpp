/*
 * damage_system.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "damage_system.h"
#include "../components/health.h"
#include "../globals.h"
#include "../commands/select_entity_command.h"
#include "../commands/call_procedure_command.h"
#include <algorithm>

void DamageSystem::update(const Time time_diff)
{
	std::for_each(cbegin(entities), cend(entities),
	[time_diff](const EntityID id)
	{
    	if(entity_system().entity(id))
    	{
    		Entity& entity = *(entity_system().entity(id));
			auto& health = entity.component<Health>();
			const bool was_alive = health.alive();

			health.update_health(time_diff);
			if(was_alive && health.alive() == false && health.on_death_exec() >= 0)
			{
				command_queue().push(std::make_unique<SelectEntityCommand>(entity.id()));
				command_queue().push(std::make_unique<CallProcedureCommand>(health.on_death_exec()));
			}
    	}
    	else
    	{
    		//error *it
    	}
	});
}

