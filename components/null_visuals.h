/*
 * null_visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_VISUALS_H_
#define COMPONENTS_NULL_VISUALS_H_

#include "visuals_enums.h"

class NullVisuals
{
public:
	template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseNullVisuals");
    }

    void update_animation(const Time) {}

    AnimationFrame animation_frame(const int, const int) const { return {}; }
    int repeat_x() const { return 0; }
    int repeat_y() const { return 0; }
    VisualLayer layer() const { return VisualLayer::FAR_BACKGROUND; }
    double look_dir_x() const { return 0.0; }
    double look_dir_y() const { return 0.0; }

    void set_repeat_x(const int) {}
    void set_repeat_y(const int) {}
    void set_layer(VisualLayer) {}
};

#endif /* COMPONENTS_NULL_VISUALS_H_ */
