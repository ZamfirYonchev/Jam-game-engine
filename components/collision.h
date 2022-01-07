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
class CollisionVariant : public ComponentVariant<Ts...>
{
public:
	using Variant = ComponentVariant<Ts...>;

    bool solid() const { return std::visit([](const auto& col){ return col.solid(); }, Variant::data); }
    SurfaceType standing_on() const { return std::visit([](const auto& col){ return col.standing_on(); }, Variant::data); }
    double on_collision_damage() const { return std::visit([](const auto& col){ return col.on_collision_damage(); }, Variant::data); }
    double elasticity() const { return std::visit([](const auto& col){ return col.elasticity(); }, Variant::data); }

    void set_solid(const bool val) { std::visit([&](auto& col){ col.set_solid(val); }, Variant::data); }
    void set_standing_on(SurfaceType surface) { std::visit([&](auto& col){ return col.set_standing_on(surface); }, Variant::data); }
    void set_collision_damage(double val) { std::visit([&](auto& col){ return col.set_collision_damage(val); }, Variant::data); }
    void set_elasticity(double val) { std::visit([&](auto& col){ return col.set_elasticity(val); }, Variant::data); }
};

#endif /* COMPONENTS_COLLISION_H_ */
