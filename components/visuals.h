/*
 * visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_VISUALS_H_
#define COMPONENTS_VISUALS_H_

#include "../types.h"
#include <ostream>

#include "component.h"
#include "visuals_enums.h"

template<typename... Ts>
class VisualsVariant : public ComponentVariant<Ts...>
{
public:
	using Variant = ComponentVariant<Ts...>;

    AnimationFrame animation_frame(const int rx, const int ry) const { return std::visit([&](const auto& vis){ return vis.animation_frame(rx, ry); }, Variant::data); }
    int repeat_x() const { return std::visit([](const auto& vis){ return vis.repeat_x(); }, Variant::data); }
    int repeat_y() const { return std::visit([](const auto& vis){ return vis.repeat_y(); }, Variant::data); }
    VisualLayer layer() const { return std::visit([](const auto& vis){ return vis.layer(); }, Variant::data); }

    void update_animation(const Time time_diff) { std::visit([&](auto& vis){ vis.update_animation(time_diff); }, Variant::data); }
    void set_repeat_x(const int val) { std::visit([&](auto& vis){ vis.set_repeat_x(val); }, Variant::data); }
    void set_repeat_y(const int val) { std::visit([&](auto& vis){ vis.set_repeat_y(val); }, Variant::data); }
    void set_layer(const VisualLayer val) { std::visit([&](auto& vis){ vis.set_layer(val); }, Variant::data); }
};

#endif /* COMPONENTS_VISUALS_H_ */
