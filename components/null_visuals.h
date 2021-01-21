/*
 * null_visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_VISUALS_H_
#define COMPONENTS_NULL_VISUALS_H_

#include "visuals.h"

class NullVisuals : public Visuals
{
public:
	using Base = Visuals;
    void print(std::ostream& to) const
    {
    	to << "UseNullVisuals ";
    }

    void update_animation(const Time time_diff) {}

    AnimationFrame animation_frame(const uint16_t rx, const uint16_t ry) const { return {}; }
    uint16_t repeat_x() const { return 0; }
    uint16_t repeat_y() const { return 0; }
    VisualLayer layer() const { return VisualLayer::FAR_BACKGROUND; }

    void set_repeat_x(uint16_t val) {}
    void set_repeat_y(uint16_t val) {}
    void set_layer(VisualLayer val) {}
};

#endif /* COMPONENTS_NULL_VISUALS_H_ */
