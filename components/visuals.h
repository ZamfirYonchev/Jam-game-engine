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
#include "null_visuals.h"
#include "character_visuals.h"
#include "flying_character_visuals.h"
#include "health_visuals.h"
#include "menu_item_visuals.h"
#include "static_visuals.h"
#include "tiled_visuals.h"
#include "animation_visuals.h"

#include "visuals_enums.h"

class Visuals
{
public:

	using Variant = std::variant<NullVisuals, CharacterVisuals, FlyingCharacterVisuals, HealthVisuals, MenuItemVisuals, StaticVisuals, TiledVisuals, AnimationVisuals>;
	Variant variant;

    AnimationFrame animation_frame(const int rx, const int ry) const { return std::visit([&](const auto& vis){ return vis.animation_frame(rx, ry); }, variant); }
    int repeat_x() const { return std::visit([](const auto& vis){ return vis.repeat_x(); }, variant); }
    int repeat_y() const { return std::visit([](const auto& vis){ return vis.repeat_y(); }, variant); }
    VisualLayer layer() const { return std::visit([](const auto& vis){ return vis.layer(); }, variant); }

    void update_animation(const Time time_diff) { std::visit([&](auto& vis){ vis.update_animation(time_diff); }, variant); }
    void set_repeat_x(const int val) { std::visit([&](auto& vis){ vis.set_repeat_x(val); }, variant); }
    void set_repeat_y(const int val) { std::visit([&](auto& vis){ vis.set_repeat_y(val); }, variant); }
    void set_layer(const VisualLayer val) { std::visit([&](auto& vis){ vis.set_layer(val); }, variant); }

    operator bool() const { return variant.index() != 0; }

    friend std::ostream& operator<< (std::ostream& out, const Visuals& component)
    {
		print(out, component.variant);
        out << std::endl;
        return out;
    }
};

#endif /* COMPONENTS_VISUALS_H_ */
