/*
 * movement.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_MOVEMENT_H_
#define COMPONENTS_MOVEMENT_H_

#include "component.h"
#include "../types.h"

template<typename... Ts>
struct MovementVariant : public ComponentVariant<Ts...>
{
	using Variant = ComponentVariant<Ts...>;

    double fx() const { return std::visit([](const auto& mov){ return mov.fx(); }, Variant::data); }
    double fy() const { return std::visit([](const auto& mov){ return mov.fy(); }, Variant::data); }
    double vx() const { return std::visit([](const auto& mov){ return mov.vx(); }, Variant::data); }
    double vy() const { return std::visit([](const auto& mov){ return mov.vy(); }, Variant::data); }
    double dx() const { return std::visit([](const auto& mov){ return mov.dx(); }, Variant::data); }
    double dy() const { return std::visit([](const auto& mov){ return mov.dy(); }, Variant::data); }
    double mass() const { return std::visit([](const auto& mov){ return mov.mass(); }, Variant::data); }
    double friction_x() const { return std::visit([](const auto& mov){ return mov.friction_x(); }, Variant::data); }
    double friction_y() const { return std::visit([](const auto& mov){ return mov.friction_y(); }, Variant::data); }
    double move_force() const { return std::visit([](const auto& mov){ return mov.move_force(); }, Variant::data); }
    double jump_force() const { return std::visit([](const auto& mov){ return mov.jump_force(); }, Variant::data); }
    bool gravity_affected() const { return std::visit([](const auto& mov){ return mov.gravity_affected(); }, Variant::data); }
    std::pair<double, double> displacement(const Time time_diff) const { return std::visit([&](const auto& mov){ return mov.displacement(time_diff); }, Variant::data); }

    void update(const Time time_diff) { std::visit([&](auto& mov){ mov.update(time_diff); }, Variant::data); }
    void set_force_x(const double val) { std::visit([&](auto& mov){ mov.set_force_x(val); }, Variant::data); }
    void set_force_y(const double val) { std::visit([&](auto& mov){ mov.set_force_y(val); }, Variant::data); }
    void set_velocity_x(const double val) { std::visit([&](auto& mov){ mov.set_velocity_x(val); }, Variant::data); }
    void set_velocity_y(const double val) { std::visit([&](auto& mov){ mov.set_velocity_y(val); }, Variant::data); }
    void set_mass(const double val) { std::visit([&](auto& mov){ mov.set_mass(val); }, Variant::data); }
    void set_friction_x(const double val) { std::visit([&](auto& mov){ mov.set_friction_x(val); }, Variant::data); }
    void set_friction_y(const double val) { std::visit([&](auto& mov){ mov.set_friction_y(val); }, Variant::data); }
    void set_move_force(const double val) { std::visit([&](auto& mov){ mov.set_move_force(val); }, Variant::data); }
    void set_jump_force(const double val) { std::visit([&](auto& mov){ mov.set_jump_force(val); }, Variant::data); }
    void set_gravity_affected(const bool val) { std::visit([&](auto& mov){ mov.set_gravity_affected(val); }, Variant::data); }

    void mod_force_x(const double val) { std::visit([&](auto& mov){ mov.mod_force_x(val); }, Variant::data); }
    void mod_force_y(const double val) { std::visit([&](auto& mov){ mov.mod_force_y(val); }, Variant::data); }
    void mod_velocity_x(const double val) { std::visit([&](auto& mov){ mov.mod_velocity_x(val); }, Variant::data); }
    void mod_velocity_y(const double val) { std::visit([&](auto& mov){ mov.mod_velocity_y(val); }, Variant::data); }
    void mod_dx(const double val) { std::visit([&](auto& mov){ mov.mod_dx(val); }, Variant::data); }
    void mod_dy(const double val) { std::visit([&](auto& mov){ mov.mod_dy(val); }, Variant::data); }
};

#endif /* COMPONENTS_MOVEMENT_H_ */
