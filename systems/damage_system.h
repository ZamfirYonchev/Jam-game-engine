/*
 * damage_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_DAMAGE_SYSTEM_H_
#define SYSTEMS_DAMAGE_SYSTEM_H_

#include "system_base.h"
#include "../components/health.h"
#include <list>
#include <utility>
#include <type_traits>

template<typename EntitySystemT, typename HealthT>
class DamageSystem : public SystemBase
{
public:
	DamageSystem(EntitySystemT& entity_system, Globals& _globals, std::stringstream& _external_commands)
	: m_entity_system(entity_system)
	, globals{_globals}
	, external_commands{_external_commands}
	{}

	void update(const Time time_diff)
	{
		if(globals(Globals::app_paused).boolean()) return;

		for(const auto id : entities)
		{
			auto& health = m_entity_system.template entity_component<HealthT>(id);
	    	if(health)
	    	{
				const bool was_alive = alive_entities.find(id) != std::cend(alive_entities);

				health.update_health(time_diff);
				if(was_alive && health.alive() == false && health.on_death_exec() > 0)
					external_commands << "Select " << id << " Call " << health.on_death_exec() << '\n';

				if(health.alive() && was_alive == false) alive_entities.insert(id);
				else if(health.alive() == false && was_alive) alive_entities.erase(id);
	    	}
	    	else
	    	{
	    		//error *it
	    	}
		}
	}

    template<typename T>
    void component_updated
	( [[maybe_unused]] const T& component
	, [[maybe_unused]] const EntityID id
	, [[maybe_unused]] const int8_t change
	)
    {
    	if constexpr(std::is_same<T, HealthT>::value)
		{
    		if(change < 0)
    			remove_id(id);
    		else if(change > 0)
    			add_id(id);

    		if(m_entity_system.template entity_component<HealthT>(id).alive())
				alive_entities.insert(id);
    		else
				alive_entities.erase(id);
		}
    }

private:
    EntitySystemT& m_entity_system;
    Globals& globals;
    std::stringstream& external_commands;
    std::unordered_set<EntityID> alive_entities;
};

#endif /* SYSTEMS_DAMAGE_SYSTEM_H_ */
