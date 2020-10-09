/*
 * damage_system.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "damage_system.h"
#include "../components/health.h"
#include "../commands/select_entity_command.h"
#include "../commands/call_procedure_command.h"
#include <algorithm>
#include "systems.h"
#include "entity_system.h"
#include "command_system.h"

void DamageSystem::update(const Time time_diff)
{
	std::for_each(cbegin(entities), cend(entities),
	[time_diff](const EntityID id)
	{
    	if(system<EntitySystem>().entity(id))
    	{
    		Entity& entity = *(system<EntitySystem>().entity(id));
			auto& health = entity.component<Health>();
			const bool was_alive = health.alive();

			health.update_health(time_diff);
			if(was_alive && health.alive() == false && health.on_death_exec() >= 0)
			{
				system<CommandSystem>().push(std::make_unique<SelectEntityCommand>(entity.id()));
				system<CommandSystem>().push(std::make_unique<CallProcedureCommand>(health.on_death_exec()));
			}
    	}
    	else
    	{
    		//error *it
    	}
	});
}

