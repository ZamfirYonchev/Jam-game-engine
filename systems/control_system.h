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

template<typename EntitySystemT>
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
			auto& control = m_entity_system.template entity_component<Control>(id);
	    	if(control)
	    	{
				const auto& health = m_entity_system.template entity_component<Health>(id);

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
					//const auto& position = entity_system.template entity_component<Position>(id);
					external_commands << "Select " << id << " Call " << control.attack_proc_id() << '\n';
					/*if(control.look_dir() == LookDir::LEFT)
					{
						//command_system.push(ModifyPositionCommand{position.x(), position.y(), 0, 0});
						//command_system.push(ModifyControlCommand{0, 0, 0, -0.0, -0.0});
						//command_system.push(ModifyControlCommand{0, 0, 0, -1, double(control.look_dir())});
					}
					else // Look dir is right
					{
						////command_system.push(new ModifyPositionCommand(-0.0, 0, 0, 0));
						////command_system.push(new ModifyPositionCommand(position->x()+position->w(), position->y(), 0, 0));
						//command_system.push(ModifyPositionCommand{position.x(), position.y(), 0, 0});
						//command_system.push(ModifyControlCommand{0, 0, 0, -0.0, -0.0});
						//command_system.push(ModifyControlCommand{0, 0, 0, 1, double(control.look_dir())});
					}*/
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
    	if constexpr(std::is_same<T, Control>::value)
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
