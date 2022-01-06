/*
 * attached_interaction.h
 *
 *  Created on: Jan 29, 2021
 *      Author: zamfi
 */

#ifndef COMPONENTS_ATTACHED_INTERACTION_H_
#define COMPONENTS_ATTACHED_INTERACTION_H_

#include "../types.h"
#include <ostream>

template<typename InteractionT>
class AttachedInteraction
{
public:
	AttachedInteraction
	( const EntityID attached_id
    , const int offset_proc_id_self
    , const int offset_proc_id_other
    , const int offset_proc_id_on_exit_self
    , ComponentAccess<InteractionT> interaction_accessor
    )
    : m_attached_id{attached_id}
    , m_offset_proc_id_self{offset_proc_id_self}
    , m_offset_proc_id_other{offset_proc_id_other}
    , m_offset_proc_id_on_exit_self{offset_proc_id_on_exit_self}
    , m_interaction_accessor{std::move(interaction_accessor)}
    {}

    template<typename ExtractorF>
    AttachedInteraction
	( ExtractorF&& extract
	, ComponentAccess<InteractionT> interaction_accessor
	)
	: AttachedInteraction
	  { extract()
	  , extract()
	  , extract()
	  , extract()
	  , std::move(interaction_accessor)
	  }
	{}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseAttachedInteraction");
    	insert(m_attached_id);
    	insert(m_offset_proc_id_self);
    	insert(m_offset_proc_id_other);
    	insert(m_offset_proc_id_on_exit_self);
    }

	void print(std::ostream& to) const
    {
    	to << "UseAttachedInteraction "
    	   << m_attached_id << " "
    	   << m_offset_proc_id_self << " "
     	   << m_offset_proc_id_other << " "
    	   << m_offset_proc_id_on_exit_self << " ";
    }

	bool is_in_group(int group_id) const
	{ return m_interaction_accessor(m_attached_id).is_in_group(group_id); }

	void set_group(int group_id, bool val)
	{ m_interaction_accessor(m_attached_id).set_group(group_id, val); }

	void clear_groups()
	{ m_interaction_accessor(m_attached_id).clear_groups(); }

	GroupID trigger_group() const
	{ return m_interaction_accessor(m_attached_id).trigger_group(); }

	ProcedureID proc_id_self() const
	{ return ProcedureID(m_interaction_accessor(m_attached_id).proc_id_self() + m_offset_proc_id_self); }

	ProcedureID proc_id_other() const
	{ return ProcedureID(m_interaction_accessor(m_attached_id).proc_id_other() + m_offset_proc_id_other); }

	ProcedureID on_exit_proc_id_self() const
	{ return ProcedureID(m_interaction_accessor(m_attached_id).on_exit_proc_id_self() + m_offset_proc_id_on_exit_self); }

	bool triggered() const
	{ return m_interaction_accessor(m_attached_id).triggered(); }

	void set_trigger_group(GroupID group)
	{ m_interaction_accessor(m_attached_id).set_trigger_group(group); }

	void set_proc_id_self(ProcedureID proc_id)
	{ m_interaction_accessor(m_attached_id).set_proc_id_self(proc_id); }

	void set_proc_id_other(ProcedureID proc_id)
	{ m_interaction_accessor(m_attached_id).set_proc_id_other(proc_id); }

	void set_on_exit_proc_id_self(ProcedureID proc_id)
	{ m_interaction_accessor(m_attached_id).set_on_exit_proc_id_self(proc_id); }

	int32_t last_triggered_groups() const
	{ return m_interaction_accessor(m_attached_id).last_triggered_groups(); }

	int32_t triggered_groups() const
	{ return m_interaction_accessor(m_attached_id).triggered_groups(); }

	void set_triggered_groups(int32_t group_vec)
	{ m_interaction_accessor(m_attached_id).set_triggered_groups(group_vec); }

	void update_last_triggered_groups()
	{ m_interaction_accessor(m_attached_id).update_last_triggered_groups(); }

	int32_t group_vector() const
	{ return m_interaction_accessor(m_attached_id).group_vector(); }

private:
	EntityID m_attached_id;
	int m_offset_proc_id_self;
	int m_offset_proc_id_other;
	int m_offset_proc_id_on_exit_self;
	ComponentAccess<InteractionT> m_interaction_accessor;
};

#endif /* COMPONENTS_ATTACHED_INTERACTION_H_ */
