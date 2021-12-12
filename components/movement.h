/*
 * movement.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_MOVEMENT_H_
#define COMPONENTS_MOVEMENT_H_

#include "../types.h"
#include <ostream>
#include <variant>
#include <utility>

#include "component.h"
#include "null_movement.h"
#include "instant_movement.h"
#include "full_movement.h"

struct Movement
{
	using Variant = std::variant<NullMovement, InstantMovement, FullMovement>;
	Variant variant;

    double fx() const { return std::visit([](const auto& mov){ return mov.fx(); }, variant); }
    double fy() const { return std::visit([](const auto& mov){ return mov.fy(); }, variant); }
    double vx() const { return std::visit([](const auto& mov){ return mov.vx(); }, variant); }
    double vy() const { return std::visit([](const auto& mov){ return mov.vy(); }, variant); }
    double dx() const { return std::visit([](const auto& mov){ return mov.dx(); }, variant); }
    double dy() const { return std::visit([](const auto& mov){ return mov.dy(); }, variant); }
    double mass() const { return std::visit([](const auto& mov){ return mov.mass(); }, variant); }
    double friction_x() const { return std::visit([](const auto& mov){ return mov.friction_x(); }, variant); }
    double friction_y() const { return std::visit([](const auto& mov){ return mov.friction_y(); }, variant); }
    double move_force() const { return std::visit([](const auto& mov){ return mov.move_force(); }, variant); }
    double jump_force() const { return std::visit([](const auto& mov){ return mov.jump_force(); }, variant); }
    bool gravity_affected() const { return std::visit([](const auto& mov){ return mov.gravity_affected(); }, variant); }
    std::pair<double, double> displacement(const Time time_diff) const { return std::visit([&](const auto& mov){ return mov.displacement(time_diff); }, variant); }

    void update(const Time time_diff) { std::visit([&](auto& mov){ mov.update(time_diff); }, variant); }
    void set_force_x(const double val) { std::visit([&](auto& mov){ mov.set_force_x(val); }, variant); }
    void set_force_y(const double val) { std::visit([&](auto& mov){ mov.set_force_y(val); }, variant); }
    void set_velocity_x(const double val) { std::visit([&](auto& mov){ mov.set_velocity_x(val); }, variant); }
    void set_velocity_y(const double val) { std::visit([&](auto& mov){ mov.set_velocity_y(val); }, variant); }
    void set_mass(const double val) { std::visit([&](auto& mov){ mov.set_mass(val); }, variant); }
    void set_friction_x(const double val) { std::visit([&](auto& mov){ mov.set_friction_x(val); }, variant); }
    void set_friction_y(const double val) { std::visit([&](auto& mov){ mov.set_friction_y(val); }, variant); }
    void set_move_force(const double val) { std::visit([&](auto& mov){ mov.set_move_force(val); }, variant); }
    void set_jump_force(const double val) { std::visit([&](auto& mov){ mov.set_jump_force(val); }, variant); }
    void set_gravity_affected(const bool val) { std::visit([&](auto& mov){ mov.set_gravity_affected(val); }, variant); }

    void mod_force_x(const double val) { std::visit([&](auto& mov){ mov.mod_force_x(val); }, variant); }
    void mod_force_y(const double val) { std::visit([&](auto& mov){ mov.mod_force_y(val); }, variant); }
    void mod_velocity_x(const double val) { std::visit([&](auto& mov){ mov.mod_velocity_x(val); }, variant); }
    void mod_velocity_y(const double val) { std::visit([&](auto& mov){ mov.mod_velocity_y(val); }, variant); }
    void mod_dx(const double val) { std::visit([&](auto& mov){ mov.mod_dx(val); }, variant); }
    void mod_dy(const double val) { std::visit([&](auto& mov){ mov.mod_dy(val); }, variant); }

    operator bool() const { return variant.index() != 0; }

	friend std::ostream& operator<< (std::ostream& out, const Movement& component)
	{
		print(out, component.variant);
	    out << '\n';
	    return out;
	}
};

#endif /* COMPONENTS_MOVEMENT_H_ */
