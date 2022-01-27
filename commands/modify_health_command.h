/*
 * modify_health_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_HEALTH_COMMAND_H_
#define COMMANDS_MODIFY_HEALTH_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../math_ext.h"

template<typename CommandSystemT, typename EntitySystemT, typename HealthT>
class ModifyHealthCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;
	Globals& globals;

	ModifyHealthCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system, Globals& _globals)
	: command_system{_command_system}
	, entity_system{_entity_system}
	, globals{_globals}
	{}

	CommandValue operator()() const
	{
    	const auto hp = command_system.exec_next();
    	const auto max_hp = command_system.exec_next();
    	const auto proc_id = command_system.exec_next();

    	const EntityID selected_entity = globals(Globals::selected_entity);
    	auto& health = entity_system.template entity_component<HealthT>(selected_entity);

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

			if(is_negative_zero(proc_id.real()))
				health.set_on_death_exec(0);
			else
				health.set_on_death_exec(health.on_death_exec() + proc_id.integer());

			return globals(Globals::selected_entity);
		}
		else
		{
			//error selected_entity
			return CommandValue{-1};
		}
	}
};


#endif /* COMMANDS_MODIFY_HEALTH_COMMAND_H_ */
