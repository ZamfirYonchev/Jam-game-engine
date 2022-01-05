/*
 * position.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_POSITION_H_
#define COMPONENTS_POSITION_H_

#include <ostream>
#include <variant>

#include "component.h"

template<typename... Ts>
struct PositionVariant
{
	using Variant = std::variant<Ts...>;
	Variant variant;

    template<typename InserterF>
    void obtain(InserterF&& inserter) const
	{
		std::visit([&](const auto& component){ return component.obtain(std::forward<InserterF>(inserter)); }, variant);
	}

	double x() const { return std::visit([](const auto& pos){ return pos.x(); }, variant); }
	double y() const { return std::visit([](const auto& pos){ return pos.y(); }, variant); }
	double w() const { return std::visit([](const auto& pos){ return pos.w(); }, variant); }
	double h() const { return std::visit([](const auto& pos){ return pos.h(); }, variant); }

	void set_x(const double value) { std::visit([&](auto& pos){ pos.set_x(value); }, variant); }
	void set_y(const double value) { std::visit([&](auto& pos){ pos.set_y(value); }, variant); }
	void set_w(const double value) { std::visit([&](auto& pos){ pos.set_w(value); }, variant); }
	void set_h(const double value) { std::visit([&](auto& pos){ pos.set_h(value); }, variant); }

	void mod_x(const double value) { std::visit([&](auto& pos){ pos.mod_x(value); }, variant); }
	void mod_y(const double value) { std::visit([&](auto& pos){ pos.mod_y(value); }, variant); }
	void mod_w(const double value) { std::visit([&](auto& pos){ pos.mod_w(value); }, variant); }
	void mod_h(const double value) { std::visit([&](auto& pos){ pos.mod_h(value); }, variant); }

    operator bool() const { return variant.index() != 0; }

private:
    template<typename... Tps>
	friend std::ostream& operator<< (std::ostream& out, const PositionVariant<Tps...>& component)
	{
		print(out, component.variant);
	    out << '\n';
	    return out;
	}
};

#endif /* COMPONENTS_POSITION_H_ */
