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

template<typename EntitySystemT>
class DamageSystem : public SystemBase
{
public:
	DamageSystem(EntitySystemT& entity_system) : m_entity_system(entity_system) {}

	void update(const Time time_diff, std::list<std::pair<EntityID, ProcedureID>>& procedure_calls)
	{
		for(const auto id : entities)
		{
			auto& health = m_entity_system.entity_component(id, (Health*)nullptr);
	    	if(health)
	    	{
				const bool was_alive = health.alive();

				health.update_health(time_diff);
				if(was_alive && health.alive() == false && health.on_death_exec() > 0)
				{
					procedure_calls.emplace_back(id, health.on_death_exec());
				}
	    	}
	    	else
	    	{
	    		//error *it
	    	}
		}
	}

    template<typename T>
    void component_updated(const T& component, const EntityID id, const int8_t change)
    {
    	if constexpr(std::is_same<T, Health>::value)
		{
    		if(change < 0)
    			remove_id(id);
    		else if(change > 0)
    			add_id(id);
		}
    }

private:
    EntitySystemT& m_entity_system;
};

#endif /* SYSTEMS_DAMAGE_SYSTEM_H_ */
