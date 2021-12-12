/*
 * health.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_HEALTH_H_
#define COMPONENTS_HEALTH_H_

#include "../types.h"
#include <ostream>

#include <variant>

#include "component.h"
#include "null_health.h"
#include "character_health.h"
#include "attached_health.h"
#include "timed_health.h"

class Health
{
public:
	using Variant  = std::variant<NullHealth, CharacterHealth, AttachedHealth, TimedHealth>;
	Variant variant;

    double hp() const { return std::visit([](const auto& health){ return health.hp(); }, variant); }
    double max_hp() const { return std::visit([](const auto& health){ return health.max_hp(); }, variant); }
    bool alive() const { return std::visit([](const auto& health){ return health.alive(); }, variant); }
    ProcedureID on_death_exec() const { return std::visit([](const auto& health){ return health.on_death_exec(); }, variant); }
    bool stunned() const { return std::visit([](const auto& health){ return health.stunned(); }, variant); }

    void set_max_hp(double hp) { std::visit([&](auto& health){ health.set_max_hp(hp); }, variant); }
    void set_hp(double hp) { std::visit([&](auto& health){ health.set_hp(hp); }, variant); }
    void set_hp_change(double hp_change) { std::visit([&](auto& health){ health.set_hp_change(hp_change); }, variant); }
    void set_on_death_exec(ProcedureID proc_id) { std::visit([&](auto& health){ health.set_on_death_exec(proc_id); }, variant); }

    void mod_hp_change(double hp_change) { std::visit([&](auto& health){ health.mod_hp_change(hp_change); }, variant); }

    void update_health(const Time time_diff) { std::visit([&](auto& health){ health.update_health(time_diff); }, variant); }

    operator bool() const { return variant.index() != 0; }

    friend std::ostream& operator<< (std::ostream& out, const Health& component)
    {
		print(out, component.variant);
        out << std::endl;
        return out;
    }
};

#endif /* COMPONENTS_HEALTH_H_ */
