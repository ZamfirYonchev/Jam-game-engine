/*
 * interaction.h
 *
 *  Created on: Nov 16, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_INTERACTION_H_
#define COMPONENTS_INTERACTION_H_

#include "../types.h"
#include <ostream>
#include <variant>

#include "component.h"

template<typename... Ts>
class InteractionVariant : public ComponentVariant<Ts...>
{
public:
	using Variant = ComponentVariant<Ts...>;

	bool is_in_group(int group_id) const { return std::visit([&](const auto& inter){ return inter.is_in_group(group_id); }, Variant::data); }
	GroupID trigger_group() const { return std::visit([](const auto& inter){ return inter.trigger_group(); }, Variant::data); }
	bool triggered() const { return std::visit([](const auto& inter){ return inter.triggered(); }, Variant::data); }
	ProcedureID proc_id_self() const { return std::visit([](const auto& inter){ return inter.proc_id_self(); }, Variant::data); }
	ProcedureID proc_id_other() const { return std::visit([](const auto& inter){ return inter.proc_id_other(); }, Variant::data); }
	ProcedureID on_exit_proc_id_self() const { return std::visit([](const auto& inter){ return inter.on_exit_proc_id_self(); }, Variant::data); }
	int32_t last_triggered_groups() const { return std::visit([](const auto& inter){ return inter.last_triggered_groups(); }, Variant::data); }
	int32_t triggered_groups() const { return std::visit([](const auto& inter){ return inter.triggered_groups(); }, Variant::data); }
	int32_t group_vector() const { return std::visit([](const auto& inter){ return inter.group_vector(); }, Variant::data); }

	void clear_groups() { std::visit([](auto& inter){ inter.clear_groups(); }, Variant::data); }
	void set_group(int group_id, bool val) { std::visit([&](auto& inter){ inter.set_group(group_id, val); }, Variant::data); }
	void set_trigger_group(GroupID group) { std::visit([&](auto& inter){ inter.set_trigger_group(group); }, Variant::data); }
	void set_triggered_groups(int32_t group_vec) { std::visit([&](auto& inter){ inter.set_triggered_groups(group_vec); }, Variant::data); }
	void update_last_triggered_groups() { std::visit([](auto& inter){ inter.update_last_triggered_groups(); }, Variant::data); }
	void set_proc_id_self(ProcedureID proc_id) { std::visit([&](auto& inter){ inter.set_proc_id_self(proc_id); }, Variant::data); }
	void set_proc_id_other(ProcedureID proc_id) { std::visit([&](auto& inter){ inter.set_proc_id_other(proc_id); }, Variant::data); }
	void set_on_exit_proc_id_self(ProcedureID proc_id) { std::visit([&](auto& inter){ inter.set_on_exit_proc_id_self(proc_id); }, Variant::data); }
};

#endif /* COMPONENTS_INTERACTION_H_ */
