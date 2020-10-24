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

class NullVisuals;

class Visuals
{
public:
	using Null = NullVisuals;
    enum RenderStates { IDLE, WALK, JUMP, FALL, ATTACK, HIT, DEAD};
    enum VisualLayer {FAR_BACKGROUND = 0, CLOSE_BACKGROUND = 1, ACTION = 2, ACTION_FRONT = 3, FOREGROUND = 4};
    static constexpr int ANIMATION_DELAY_MS = 50;
    static constexpr int NUM_OF_LAYERS = 5;

    virtual ~Visuals() {}
    virtual void print(std::ostream& to) const = 0;

    virtual RenderStates state() const = 0;
    virtual uint8_t animation_sprite(uint16_t rx, uint16_t ry) const = 0;
    virtual AbsSpritesheetID spritesheet_id() = 0;
    virtual bool animation_count_max() const = 0;
    virtual uint16_t repeat_x() const = 0;
    virtual uint16_t repeat_y() const = 0;
    virtual VisualLayer layer() const = 0;

    virtual void set_new_state(RenderStates new_state) = 0;
    virtual void set_spritesheet_id(AbsSpritesheetID spr_id) = 0;
    virtual void set_repeat_x(uint16_t val) = 0;
    virtual void set_repeat_y(uint16_t val) = 0;
    virtual void set_layer(VisualLayer val) = 0;

    virtual void advance_animation(Time time_diff) = 0;

    static Visuals* null;

    operator bool() const { return this != null; }

    friend std::ostream& operator<< (std::ostream& out, const Visuals& component)
    {
    	component.print(out);
        out << std::endl;
        return out;
    }
};

#endif /* COMPONENTS_VISUALS_H_ */
