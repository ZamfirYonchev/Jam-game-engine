/*
 * control.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_CONTROL_H_
#define COMPONENTS_CONTROL_H_

#include "component.h"
#include "../types.h"
#include "control_enums.h"

template<typename... Ts>
struct ControlVariant : public ComponentVariant<Ts...>
{
	using Variant = ComponentVariant<Ts...>;

    double decision_vertical() const { return std::visit([](const auto& ctrl){ return ctrl.decision_vertical(); }, Variant::data); }
    bool decision_attack() const { return std::visit([](const auto& ctrl){ return ctrl.decision_attack(); }, Variant::data); }
    double decision_walk() const { return std::visit([](const auto& ctrl){ return ctrl.decision_walk(); }, Variant::data); }
    ProcedureID attack_proc_id() const { return std::visit([](const auto& ctrl){ return ctrl.attack_proc_id(); }, Variant::data); }
    LookDir look_dir() const { return std::visit([](const auto& ctrl){ return ctrl.look_dir(); }, Variant::data); }

    void set_decision_vertical(double val) { std::visit([&](auto& ctrl){ ctrl.set_decision_vertical(val); }, Variant::data); }
    void set_decision_attack(bool val) { std::visit([&](auto& ctrl){ ctrl.set_decision_attack(val); }, Variant::data); }
    void set_decision_walk(double val) { std::visit([&](auto& ctrl){ ctrl.set_decision_walk(val); }, Variant::data); }
    void mod_decision_vertical(double val) { std::visit([&](auto& ctrl){ ctrl.mod_decision_vertical(val); }, Variant::data); }
    void mod_decision_walk(double val) { std::visit([&](auto& ctrl){ ctrl.mod_decision_walk(val); }, Variant::data); }
    void set_attack_proc_id(ProcedureID val) { std::visit([&](auto& ctrl){ ctrl.set_attack_proc_id(val); }, Variant::data); }
    void set_look_dir(LookDir val) { std::visit([&](auto& ctrl){ ctrl.set_look_dir(val); }, Variant::data); }

    void update_decisions(const Time time) { std::visit([&](auto& ctrl){ ctrl.update_decisions(time); }, Variant::data); }
    void clear_decisions() { std::visit([](auto& ctrl){ ctrl.clear_decisions(); }, Variant::data); }
};

#endif /* COMPONENTS_CONTROL_H_ */
