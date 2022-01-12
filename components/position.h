/*
 * position.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_POSITION_H_
#define COMPONENTS_POSITION_H_

#include "component.h"

template<typename... Ts>
struct PositionVariant : public ComponentVariant<Ts...>
{
	using Variant = ComponentVariant<Ts...>;

	double x() const { return std::visit([](const auto& pos){ return pos.x(); }, Variant::data); }
	double y() const { return std::visit([](const auto& pos){ return pos.y(); }, Variant::data); }
	double w() const { return std::visit([](const auto& pos){ return pos.w(); }, Variant::data); }
	double h() const { return std::visit([](const auto& pos){ return pos.h(); }, Variant::data); }

	void set_x(const double value) { std::visit([&](auto& pos){ pos.set_x(value); }, Variant::data); }
	void set_y(const double value) { std::visit([&](auto& pos){ pos.set_y(value); }, Variant::data); }
	void set_w(const double value) { std::visit([&](auto& pos){ pos.set_w(value); }, Variant::data); }
	void set_h(const double value) { std::visit([&](auto& pos){ pos.set_h(value); }, Variant::data); }

	void mod_x(const double value) { std::visit([&](auto& pos){ pos.mod_x(value); }, Variant::data); }
	void mod_y(const double value) { std::visit([&](auto& pos){ pos.mod_y(value); }, Variant::data); }
	void mod_w(const double value) { std::visit([&](auto& pos){ pos.mod_w(value); }, Variant::data); }
	void mod_h(const double value) { std::visit([&](auto& pos){ pos.mod_h(value); }, Variant::data); }
};

#endif /* COMPONENTS_POSITION_H_ */
