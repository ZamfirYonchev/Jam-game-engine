/*
 * modify_health_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_HEALTH_COMMAND_H_
#define COMMANDS_MODIFY_HEALTH_COMMAND_H_

#include "../math_ext.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ModifyHealthCommand
{
public:
	ModifyHealthCommand(double max_hp, double hp, double hp_change)
	: m_max_hp(max_hp)
	, m_hp(hp)
	, m_hp_change(hp_change)
	{}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	Health& health = entity_system.entity_component(entity_system.previous_entity_id(), (Health*)nullptr);

		if(health)
		{
			if(is_negative_zero(m_max_hp))
				health.set_max_hp(0);
			else
				health.set_max_hp(health.max_hp() + m_max_hp);

			if(is_negative_zero(m_hp))
				health.set_hp(0);
			else
				health.set_hp(health.hp() + m_hp);

			if(is_negative_zero(m_hp_change))
				health.set_hp_change(0);
			else
				health.mod_hp_change(m_hp_change);
		}
		else
		{
			//error entity_system.previous_entity_id()
		}
	}

private:
	double m_max_hp, m_hp, m_hp_change;
};


#endif /* COMMANDS_MODIFY_HEALTH_COMMAND_H_ */
