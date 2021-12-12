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
#include "../command_value.h"

class Interaction;

class AttachedInteraction
{
public:
	AttachedInteraction
	( const EntityID attached_id
    , const int offset_proc_id_self
    , const int offset_proc_id_other
    , const int offset_proc_id_on_exit_self
    , const std::function<Interaction&(const EntityID id)>& interaction_accessor
    )
    : m_attached_id{attached_id}
    , m_interaction_accessor{interaction_accessor}
    , m_offset_proc_id_self{offset_proc_id_self}
    , m_offset_proc_id_other{offset_proc_id_other}
    , m_offset_proc_id_on_exit_self{offset_proc_id_on_exit_self}
    {}

    template<typename ExtractorF>
    AttachedInteraction
	( ExtractorF&& extract
	, std::function<Interaction&(const EntityID id)> interaction_accessor
	)
	: AttachedInteraction
	  { extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , std::move(interaction_accessor)
	  }
	{}

	void print(std::ostream& to) const
    {
    	to << "UseAttachedInteraction "
    	   << m_attached_id << " "
    	   << m_offset_proc_id_self << " "
     	   << m_offset_proc_id_other << " "
    	   << m_offset_proc_id_on_exit_self << " ";
    }

	bool is_in_group(int group_id) const;
	void set_group(int group_id, bool val);
	void clear_groups();

	GroupID trigger_group() const;
	ProcedureID proc_id_self() const;
	ProcedureID proc_id_other() const;
	ProcedureID on_exit_proc_id_self() const;
	bool triggered() const;

	void set_trigger_group(GroupID group);
	void set_proc_id_self(ProcedureID proc_id);
	void set_proc_id_other(ProcedureID proc_id);
	void set_on_exit_proc_id_self(ProcedureID proc_id);

	int32_t last_triggered_groups() const;
	int32_t triggered_groups() const;
	void set_triggered_groups(int32_t group_vec);
	void update_last_triggered_groups();
	int32_t group_vector() const;

private:
	EntityID m_attached_id;
    std::function<Interaction&(const EntityID id)> m_interaction_accessor;
	int m_offset_proc_id_self;
	int m_offset_proc_id_other;
	int m_offset_proc_id_on_exit_self;
};

#endif /* COMPONENTS_ATTACHED_INTERACTION_H_ */
