/*
 * attached_interaction.cpp
 *
 *  Created on: Nov 27, 2021
 *      Author: zamfi
 */

#include "attached_interaction.h"
#include "interaction.h"

bool AttachedInteraction::is_in_group(int group_id) const
{ return m_interaction_accessor(m_attached_id).is_in_group(group_id); }

void AttachedInteraction::set_group(int group_id, bool val)
{ m_interaction_accessor(m_attached_id).set_group(group_id, val); }

void AttachedInteraction::clear_groups()
{ m_interaction_accessor(m_attached_id).clear_groups(); }

GroupID AttachedInteraction::trigger_group() const
{ return m_interaction_accessor(m_attached_id).trigger_group(); }

ProcedureID AttachedInteraction::proc_id_self() const
{ return ProcedureID(m_interaction_accessor(m_attached_id).proc_id_self() + m_offset_proc_id_self); }

ProcedureID AttachedInteraction::proc_id_other() const
{ return ProcedureID(m_interaction_accessor(m_attached_id).proc_id_other() + m_offset_proc_id_other); }

ProcedureID AttachedInteraction::on_exit_proc_id_self() const
{ return ProcedureID(m_interaction_accessor(m_attached_id).on_exit_proc_id_self() + m_offset_proc_id_on_exit_self); }

bool AttachedInteraction::triggered() const
{ return m_interaction_accessor(m_attached_id).triggered(); }

void AttachedInteraction::set_trigger_group(GroupID group)
{ m_interaction_accessor(m_attached_id).set_trigger_group(group); }

void AttachedInteraction::set_proc_id_self(ProcedureID proc_id)
{ m_interaction_accessor(m_attached_id).set_proc_id_self(proc_id); }

void AttachedInteraction::set_proc_id_other(ProcedureID proc_id)
{ m_interaction_accessor(m_attached_id).set_proc_id_other(proc_id); }

void AttachedInteraction::set_on_exit_proc_id_self(ProcedureID proc_id)
{ m_interaction_accessor(m_attached_id).set_on_exit_proc_id_self(proc_id); }

int32_t AttachedInteraction::last_triggered_groups() const
{ return m_interaction_accessor(m_attached_id).last_triggered_groups(); }

int32_t AttachedInteraction::triggered_groups() const
{ return m_interaction_accessor(m_attached_id).triggered_groups(); }

void AttachedInteraction::set_triggered_groups(int32_t group_vec)
{ m_interaction_accessor(m_attached_id).set_triggered_groups(group_vec); }

void AttachedInteraction::update_last_triggered_groups()
{ m_interaction_accessor(m_attached_id).update_last_triggered_groups(); }

int32_t AttachedInteraction::group_vector() const
{ return m_interaction_accessor(m_attached_id).group_vector(); }
