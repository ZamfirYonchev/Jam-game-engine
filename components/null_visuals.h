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
    void print(std::ostream& to) const
    {
    	to << "UseNullVisuals ";
    }

    RenderStates state() const { return IDLE; }
    void set_new_state(RenderStates new_state) {}
    void advance_animation(Time time_diff) {}
    uint8_t animation_sprite(uint16_t rx, uint16_t ry) const { return 0; }
    bool animation_count_max() const { return true; }
    SpritesheetID spritesheet_id() { return 0; }
    void set_spritesheet_id(SpritesheetID spr_id) {}
    uint16_t repeat_x() const { return 0; }
    uint16_t repeat_y() const { return 0; }
    void set_repeat_x(uint16_t val) {}
    void set_repeat_y(uint16_t val) {}
    VisualLayer layer() const { return FAR_BACKGROUND; }
    void set_layer(VisualLayer val) {}
};

#endif /* COMPONENTS_NULL_VISUALS_H_ */
