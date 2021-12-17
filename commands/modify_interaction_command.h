/*
 * modify_interaction_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_INTERACTION_COMMAND_H_
#define COMMANDS_MODIFY_INTERACTION_COMMAND_H_

#include "../command_value.h"
#include "../globals.h"
#include "../math_ext.h"

template<typename CommandSystemT, typename EntitySystemT>
class ModifyInteractionCommand
{
public:
	CommandSystemT& command_system;
	EntitySystemT& entity_system;
	Globals& globals;

	ModifyInteractionCommand(CommandSystemT& _command_system, EntitySystemT& _entity_system, Globals& _globals)
	: command_system{_command_system}
	, entity_system{_entity_system}
	, globals{_globals}
	{}

	CommandValue operator()() const
	{
    	const auto groups = command_system.exec_next();
    	const auto group_value = command_system.exec_next();
    	const auto trigger_group = command_system.exec_next();
    	const auto proc_id_self = command_system.exec_next();
    	const auto proc_id_other = command_system.exec_next();
    	const auto on_exit_proc_id_self = command_system.exec_next();

    	const EntityID selected_entity = globals(Globals::selected_entity).integer();
    	Interaction& interaction = entity_system.template entity_component<Interaction>(selected_entity);

		if(interaction)
		{
			if(is_negative_zero(groups.real()))
				interaction.clear_groups();
			else
				if(is_negative_zero(group_value.real()))
					interaction.set_group(groups.integer(), false);
				else
					interaction.set_group(groups.integer(), group_value.boolean() ^ interaction.is_in_group(groups.integer()));

			if(is_negative_zero(trigger_group.real()))
				interaction.set_trigger_group(0);
			else
				interaction.set_trigger_group(interaction.trigger_group() + trigger_group.integer());

			if(is_negative_zero(proc_id_self.real()))
				interaction.set_proc_id_self(ProcedureID{0});
			else
				interaction.set_proc_id_self(ProcedureID(interaction.proc_id_self() + proc_id_self.integer()));

			if(is_negative_zero(proc_id_other.real()))
				interaction.set_proc_id_other(ProcedureID{0});
			else
				interaction.set_proc_id_other(ProcedureID(interaction.proc_id_other() + proc_id_other.integer()));

			if(is_negative_zero(on_exit_proc_id_self.real()))
				interaction.set_on_exit_proc_id_self(ProcedureID{0});
			else
				interaction.set_on_exit_proc_id_self(ProcedureID(interaction.on_exit_proc_id_self() + on_exit_proc_id_self.integer()));

			return globals(Globals::selected_entity);
		}
		else
		{
			//error selected_entity
			return CommandValue{-1};
		}
	}
};

#endif /* COMMANDS_MODIFY_INTERACTION_COMMAND_H_ */
