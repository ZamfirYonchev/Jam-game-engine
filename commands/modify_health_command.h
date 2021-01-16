/*
 * modify_health_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_HEALTH_COMMAND_H_
#define COMMANDS_MODIFY_HEALTH_COMMAND_H_

#include "command_return_value.h"
#include "../globals.h"
#include "../math_ext.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;

class ModifyHealthCommand
{
public:
    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto max_hp = command_system.exec_next();
    	const auto hp = command_system.exec_next();
    	const auto hp_change = command_system.exec_next();

    	Health& health = entity_system.entity_component(entity_system.previous_entity_id(), (Health*)nullptr);

		if(health)
		{
			if(is_negative_zero(max_hp.real()))
				health.set_max_hp(0);
			else
				health.set_max_hp(health.max_hp() + max_hp.real());

			if(is_negative_zero(hp.real()))
				health.set_hp(0);
			else
				health.set_hp(health.hp() + hp.real());

			if(is_negative_zero(hp_change.real()))
				health.set_hp_change(0);
			else
				health.mod_hp_change(hp_change.real());

			return CommandReturnValue{0l};
		}
		else
		{
			//error entity_system.previous_entity_id()
			return CommandReturnValue{-1l};
		}
	}
};


#endif /* COMMANDS_MODIFY_HEALTH_COMMAND_H_ */
