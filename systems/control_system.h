/*
 * control_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_CONTROL_SYSTEM_H_
#define SYSTEMS_CONTROL_SYSTEM_H_

#include "system_base.h"
#include "../components/control.h"
#include "../components/health.h"
#include <list>
#include <utility>
#include <type_traits>

template<typename EntitySystemT, typename ControlT, typename HealthT>
class ControlSystem : public SystemBase
{
public:
	ControlSystem(EntitySystemT& entity_system, Globals& _globals, std::stringstream& _external_commands)
	: m_entity_system(entity_system)
	, globals{_globals}
	, external_commands{_external_commands}
	{}

	void update(const Time time_diff)
	{
		if(globals(Globals::app_paused).boolean()) return;

		for(const auto id : entities)
		{
			auto& control = m_entity_system.template entity_component<ControlT>(id);
	    	if(control)
	    	{
				const auto& health = m_entity_system.template entity_component<HealthT>(id);

				if(health.alive())
				{
					control.update_decisions(time_diff);
					if(health.stunned())
					{
						control.mod_decision_walk(-0.5*control.decision_walk());
						control.mod_decision_vertical(-0.5*control.decision_vertical());
					}
				}
				else
					control.clear_decisions();


				if(control.decision_attack() && control.attack_proc_id() > 0)
				{
					external_commands << "Select " << id << " Call " << control.attack_proc_id() << '\n';
				}
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
    	if constexpr(std::is_same<T, ControlT>::value)
		{
    		if(change < 0)
    			remove_id(id);
    		else if(change > 0)
    			add_id(id);
		}
    }

private:
    EntitySystemT& m_entity_system;
    Globals& globals;
    std::stringstream& external_commands;
};


#endif /* SYSTEMS_CONTROL_SYSTEM_H_ */
