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

void DamageSystem::update(Time time_diff)
{
    for(auto it = entities.begin(); it != entities.end(); ++it)
    {
    	Health* health = globals.entity_system.entity(*it)->health();
    	bool was_alive = health->alive();
        health->update_health(time_diff);
        if(was_alive && health->alive() == false && health->on_death_exec() >= 0)
        {
        	globals.command_queue.push(new SelectEntityCommand(globals.entity_system.entity(*it)->id()));
        	globals.command_queue.push(new CallProcedureCommand(health->on_death_exec()));
        }
    }
}

