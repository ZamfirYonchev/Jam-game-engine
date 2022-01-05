/*
 * collision.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_COLLISION_H_
#define COMPONENTS_COLLISION_H_

#include "../types.h"
#include <ostream>
#include <variant>

#include "component.h"
#include "collision_enums.h"

template<typename... Ts>
class CollisionVariant
{
public:
	using Variant = std::variant<Ts...>;
	Variant variant;

    bool solid() const { return std::visit([](const auto& col){ return col.solid(); }, variant); }
    SurfaceType standing_on() const { return std::visit([](const auto& col){ return col.standing_on(); }, variant); }
    double on_collision_damage() const { return std::visit([](const auto& col){ return col.on_collision_damage(); }, variant); }
    double elasticity() const { return std::visit([](const auto& col){ return col.elasticity(); }, variant); }

    void set_solid(const bool val) { std::visit([&](auto& col){ col.set_solid(val); }, variant); }
    void set_standing_on(SurfaceType surface) { std::visit([&](auto& col){ return col.set_standing_on(surface); }, variant); }
    void set_collision_damage(double val) { std::visit([&](auto& col){ return col.set_collision_damage(val); }, variant); }
    void set_elasticity(double val) { std::visit([&](auto& col){ return col.set_elasticity(val); }, variant); }

    operator bool() const { return variant.index() != 0; }

    template<typename... Tps>
    friend std::ostream& operator<< (std::ostream& out, const CollisionVariant<Tps...>& component)
    {
		print(out, component.variant);
        out << std::endl;
        return out;
    }
};

#endif /* COMPONENTS_COLLISION_H_ */
