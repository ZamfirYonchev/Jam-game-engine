/*
 * control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_CONTROL_H_
#define COMPONENTS_CONTROL_H_

#include <cinttypes>
#include "../types.h"
#include <ostream>

#include "component.h"
#include "control_enums.h"

template<typename... Ts>
struct ControlVariant
{
	using Variant  = std::variant<Ts...>;
	Variant variant;

    double decision_vertical() const { return std::visit([](const auto& ctrl){ return ctrl.decision_vertical(); }, variant); }
    bool decision_attack() const { return std::visit([](const auto& ctrl){ return ctrl.decision_attack(); }, variant); }
    double decision_walk() const { return std::visit([](const auto& ctrl){ return ctrl.decision_walk(); }, variant); }
    ProcedureID attack_proc_id() const { return std::visit([](const auto& ctrl){ return ctrl.attack_proc_id(); }, variant); }
    LookDir look_dir() const { return std::visit([](const auto& ctrl){ return ctrl.look_dir(); }, variant); }

    void set_decision_vertical(double val) { std::visit([&](auto& ctrl){ ctrl.set_decision_vertical(val); }, variant); }
    void set_decision_attack(bool val) { std::visit([&](auto& ctrl){ ctrl.set_decision_attack(val); }, variant); }
    void set_decision_walk(double val) { std::visit([&](auto& ctrl){ ctrl.set_decision_walk(val); }, variant); }
    void mod_decision_vertical(double val) { std::visit([&](auto& ctrl){ ctrl.mod_decision_vertical(val); }, variant); }
    void mod_decision_walk(double val) { std::visit([&](auto& ctrl){ ctrl.mod_decision_walk(val); }, variant); }
    void set_attack_proc_id(ProcedureID val) { std::visit([&](auto& ctrl){ ctrl.set_attack_proc_id(val); }, variant); }
    void set_look_dir(LookDir val) { std::visit([&](auto& ctrl){ ctrl.set_look_dir(val); }, variant); }

    void update_decisions(const Time time) { std::visit([&](auto& ctrl){ ctrl.update_decisions(time); }, variant); }
    void clear_decisions() { std::visit([](auto& ctrl){ ctrl.clear_decisions(); }, variant); }

    operator bool() const { return variant.index() != 0; }

    template<typename... Tps>
	friend std::ostream& operator<< (std::ostream& out, const ControlVariant<Tps...>& component)
	{
		print(out, component.variant);
	    out << '\n';
	    return out;
	}
};

#endif /* COMPONENTS_CONTROL_H_ */
