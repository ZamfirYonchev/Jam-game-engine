/*
 * health.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_HEALTH_H_
#define COMPONENTS_HEALTH_H_

#include "component.h"
#include "../types.h"

template<typename... Ts>
class HealthVariant : public ComponentVariant<Ts...>
{
public:
	using Variant = ComponentVariant<Ts...>;

    double hp() const { return std::visit([](const auto& health){ return health.hp(); }, Variant::data); }
    double max_hp() const { return std::visit([](const auto& health){ return health.max_hp(); }, Variant::data); }
    bool alive() const { return std::visit([](const auto& health){ return health.alive(); }, Variant::data); }
    ProcedureID on_death_exec() const { return std::visit([](const auto& health){ return health.on_death_exec(); }, Variant::data); }
    bool stunned() const { return std::visit([](const auto& health){ return health.stunned(); }, Variant::data); }

    void set_max_hp(const double hp) { std::visit([&](auto& health){ health.set_max_hp(hp); }, Variant::data); }
    void set_hp(const double hp) { std::visit([&](auto& health){ health.set_hp(hp); }, Variant::data); }
    void set_on_death_exec(const ProcedureID proc_id) { std::visit([&](auto& health){ health.set_on_death_exec(proc_id); }, Variant::data); }

    void mod_hp(const double hp_change) { std::visit([&](auto& health){ health.mod_hp(hp_change); }, Variant::data); }

    void update_health(const Time time_diff) { std::visit([&](auto& health){ health.update_health(time_diff); }, Variant::data); }
};

#endif /* COMPONENTS_HEALTH_H_ */
