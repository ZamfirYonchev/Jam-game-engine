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
class InteractionVariant
{
public:
	using Variant  = std::variant<Ts...>;
	Variant variant;

	bool is_in_group(int group_id) const { return std::visit([&](const auto& inter){ return inter.is_in_group(group_id); }, variant); }
	GroupID trigger_group() const { return std::visit([](const auto& inter){ return inter.trigger_group(); }, variant); }
	bool triggered() const { return std::visit([](const auto& inter){ return inter.triggered(); }, variant); }
	ProcedureID proc_id_self() const { return std::visit([](const auto& inter){ return inter.proc_id_self(); }, variant); }
	ProcedureID proc_id_other() const { return std::visit([](const auto& inter){ return inter.proc_id_other(); }, variant); }
	ProcedureID on_exit_proc_id_self() const { return std::visit([](const auto& inter){ return inter.on_exit_proc_id_self(); }, variant); }
	int32_t last_triggered_groups() const { return std::visit([](const auto& inter){ return inter.last_triggered_groups(); }, variant); }
	int32_t triggered_groups() const { return std::visit([](const auto& inter){ return inter.triggered_groups(); }, variant); }
	int32_t group_vector() const { return std::visit([](const auto& inter){ return inter.group_vector(); }, variant); }

	void clear_groups() { std::visit([](auto& inter){ inter.clear_groups(); }, variant); }
	void set_group(int group_id, bool val) { std::visit([&](auto& inter){ inter.set_group(group_id, val); }, variant); }
	void set_trigger_group(GroupID group) { std::visit([&](auto& inter){ inter.set_trigger_group(group); }, variant); }
	void set_triggered_groups(int32_t group_vec) { std::visit([&](auto& inter){ inter.set_triggered_groups(group_vec); }, variant); }
	void update_last_triggered_groups() { std::visit([](auto& inter){ inter.update_last_triggered_groups(); }, variant); }
	void set_proc_id_self(ProcedureID proc_id) { std::visit([&](auto& inter){ inter.set_proc_id_self(proc_id); }, variant); }
	void set_proc_id_other(ProcedureID proc_id) { std::visit([&](auto& inter){ inter.set_proc_id_other(proc_id); }, variant); }
	void set_on_exit_proc_id_self(ProcedureID proc_id) { std::visit([&](auto& inter){ inter.set_on_exit_proc_id_self(proc_id); }, variant); }

    operator bool() const { return variant.index() != 0; }

    template<typename... Tps>
    friend std::ostream& operator<< (std::ostream& out, const InteractionVariant<Tps...>& component)
    {
		print(out, component.variant);
        out << std::endl;
        return out;
    }
};

#endif /* COMPONENTS_INTERACTION_H_ */
