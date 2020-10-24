/*
 * modify_interaction_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_INTERACTION_COMMAND_H_
#define COMMANDS_MODIFY_INTERACTION_COMMAND_H_

#include "../math_ext.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ModifyInteractionCommand
{
public:
	ModifyInteractionCommand(double group, double value, double trigger_group, double proc_id_self, double on_exit_proc_id_self, double proc_id_other)
	: m_group(group)
	, m_value(value)
	, m_trigger_group(trigger_group)
	, m_proc_id_self(proc_id_self)
	, m_on_exit_proc_id_self(on_exit_proc_id_self)
	, m_proc_id_other(proc_id_other)
	{}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	Interaction& interaction = entity_system.entity_component(entity_system.previous_entity_id(), (Interaction*)nullptr);

		if(interaction)
		{
			if(is_negative_zero(m_group))
				interaction.clear_groups();
			else
				if(is_negative_zero(m_value))
					interaction.set_group(m_group, false);
				else
					interaction.set_group(m_group, bool(m_value) ^ interaction.is_in_group(m_group));

			if(is_negative_zero(m_trigger_group))
				interaction.set_trigger_group(0);
			else
				interaction.set_trigger_group(interaction.trigger_group() + m_trigger_group);

			if(is_negative_zero(m_proc_id_self))
				interaction.set_proc_id_self(ProcedureID{0});
			else
				interaction.set_proc_id_self(ProcedureID{interaction.proc_id_self() + int(m_proc_id_self)});

			if(is_negative_zero(m_proc_id_other))
				interaction.set_proc_id_other(ProcedureID{0});
			else
				interaction.set_proc_id_other(ProcedureID{interaction.proc_id_other() + int(m_proc_id_other)});

			if(is_negative_zero(m_on_exit_proc_id_self))
				interaction.set_on_exit_proc_id_self(ProcedureID{0});
			else
				interaction.set_on_exit_proc_id_self(ProcedureID{interaction.on_exit_proc_id_self() + int(m_on_exit_proc_id_self)});
		}
		else
		{
			//error entity_system.previous_entity_id()
		}
	}

private:
	double m_group, m_value, m_trigger_group, m_proc_id_self, m_on_exit_proc_id_self, m_proc_id_other;
};

#endif /* COMMANDS_MODIFY_INTERACTION_COMMAND_H_ */
