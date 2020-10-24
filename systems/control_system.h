/*
 * control_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_CONTROL_SYSTEM_H_
#define SYSTEMS_CONTROL_SYSTEM_H_

#include "system_base.h"
#include <sstream>
#include "../components/control.h"
#include "../components/health.h"
#include "../commands/call_procedure_command.h"
#include "../commands/modify_position_command.h"
#include "../commands/modify_control_command.h"
#include <algorithm>
#include <list>
#include <utility>
#include <type_traits>

template<typename EntitySystemT>
class ControlSystem : public SystemBase
{
public:
	ControlSystem(EntitySystemT& entity_system) : m_entity_system(entity_system) {}

	void update(const Time time_diff, EntitySystemT& entity_system, std::list<std::pair<EntityID, ProcedureID>>& procedure_calls)
	{
		for(const auto id : entities)
		{
			auto& control = entity_system.entity_component(id, (Control*)nullptr);
	    	if(control)
	    	{
				const auto& health = entity_system.entity_component(id, (Health*)nullptr);

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
					//const auto& position = entity_system.entity_component(id, (Position*)nullptr);
					procedure_calls.emplace_back(id, control.attack_proc_id());
					if(control.look_dir() == Control::LEFT)
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
					}
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
};


#endif /* SYSTEMS_CONTROL_SYSTEM_H_ */
