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

    AnimationFrame animation_frame(const int rx, const int ry) const { return {}; }
    int repeat_x() const { return 0; }
    int repeat_y() const { return 0; }
    VisualLayer layer() const { return VisualLayer::FAR_BACKGROUND; }

    void set_repeat_x(const int val) {}
    void set_repeat_y(const int val) {}
    void set_layer(VisualLayer val) {}
};

#endif /* COMPONENTS_NULL_VISUALS_H_ */
