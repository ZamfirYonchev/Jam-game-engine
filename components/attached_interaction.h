/*
 * attached_interaction.h
 *
 *  Created on: Jan 29, 2021
 *      Author: zamfi
 */

#ifndef COMPONENTS_ATTACHED_INTERACTION_H_
#define COMPONENTS_ATTACHED_INTERACTION_H_

#include "interaction.h"
#include "../commands/use_component_command.h"

//TODO to store entity system reference rather than attached interaction reference
class AttachedInteraction : public Interaction
{
public:
	using Base = Interaction;

	template<typename EntitySystemT>
	AttachedInteraction
		(const EntityID attached_id
	   , const int offset_proc_id_self
	   , const int offset_proc_id_other
	   , const int offset_proc_id_on_exit_self
	   , EntitySystemT& entity_system)
	: m_attached_id{attached_id}
	, m_attached_interaction{entity_system.template entity_component<Interaction>(attached_id)}
	, m_offset_proc_id_self{offset_proc_id_self}
	, m_offset_proc_id_other{offset_proc_id_other}
	, m_offset_proc_id_on_exit_self{offset_proc_id_on_exit_self}
	{}

    void print(std::ostream& to) const
    {
    	to << "UseAttachedInteraction "
    	   << m_attached_id << " "
    	   << m_offset_proc_id_self << " "
     	   << m_offset_proc_id_other << " "
    	   << m_offset_proc_id_on_exit_self << " ";
    }

	bool is_in_group(int group_id) const { return m_attached_interaction.is_in_group(group_id); }
	void set_group(int group_id, bool val) { m_attached_interaction.set_group(group_id, val); }
	void clear_groups() { m_attached_interaction.clear_groups(); }

	int8_t trigger_group() const { return m_attached_interaction.trigger_group(); }
	ProcedureID proc_id_self() const { return ProcedureID(m_attached_interaction.proc_id_self() + m_offset_proc_id_self); }
	ProcedureID proc_id_other() const { return ProcedureID(m_attached_interaction.proc_id_other() + m_offset_proc_id_other); }
	ProcedureID on_exit_proc_id_self() const { return ProcedureID(m_attached_interaction.on_exit_proc_id_self() + m_offset_proc_id_on_exit_self); }
	bool triggered() const { return m_attached_interaction.triggered(); }

	void set_trigger_group(int8_t group) { m_attached_interaction.set_trigger_group(group); }
	void set_proc_id_self(ProcedureID proc_id) { m_attached_interaction.set_proc_id_self(proc_id); }
	void set_proc_id_other(ProcedureID proc_id) { m_attached_interaction.set_proc_id_other(proc_id); }
	void set_on_exit_proc_id_self(ProcedureID proc_id) { m_attached_interaction.set_on_exit_proc_id_self(proc_id); }

	int32_t last_triggered_groups() const { return m_attached_interaction.last_triggered_groups(); }
	int32_t triggered_groups() const { return m_attached_interaction.triggered_groups(); }
	void set_triggered_groups(int32_t group_vec) { m_attached_interaction.set_triggered_groups(group_vec); }
	void update_last_triggered_groups() { m_attached_interaction.update_last_triggered_groups(); }
	int32_t group_vector() const { return m_attached_interaction.group_vector(); }

private:
	EntityID m_attached_id;
	Interaction& m_attached_interaction;
	int m_offset_proc_id_self;
	int m_offset_proc_id_other;
	int m_offset_proc_id_on_exit_self;
};

template<>
template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
CommandReturnValue UseComponentCommand<AttachedInteraction>::operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
{
	const auto attached_id = command_system.exec_next();
	const auto offset_proc_id_self = command_system.exec_next();
	const auto offset_proc_id_other = command_system.exec_next();
	const auto offset_proc_id_on_exit_self = command_system.exec_next();

	set_component(entity_system
				, rendering_system
				, all_systems
				, globals,
					{ attached_id.integer()
					, offset_proc_id_self.integer()
					, offset_proc_id_other.integer()
					, offset_proc_id_on_exit_self.integer()
					, entity_system}
				);

	return CommandReturnValue{0.0};
}

#endif /* COMPONENTS_ATTACHED_INTERACTION_H_ */
