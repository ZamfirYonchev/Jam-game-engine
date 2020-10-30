/*
 * static_visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_STATIC_VISUALS_H_
#define COMPONENTS_STATIC_VISUALS_H_

#include "visuals.h"

class StaticVisuals : public Visuals
{
public:
	using Base = Visuals;
	StaticVisuals(const SpritesheetID spr_id, const int sprite)
	: m_spr_id(spr_id)
	, m_sprite(sprite)
	, m_layer(VisualLayer::FAR_BACKGROUND)
	{}

    void print(std::ostream& to) const
    {
    	to << "UseStaticVisuals "
    	   << m_spr_id << " "
    	   << m_sprite << " ";
    }

    RenderStates state() const { return RenderStates::IDLE; }
    void set_new_state(RenderStates new_state) {}
    void advance_animation(Time time_diff) {}
    uint8_t animation_sprite(uint16_t rx, uint16_t ry) const { return m_sprite; }
    bool animation_count_max() const { return true; }
    SpritesheetID spritesheet_id() { return m_spr_id; }
    void set_spritesheet_id(SpritesheetID spr_id) { m_spr_id = spr_id; }
    uint16_t repeat_x() const { return 1; }
    virtual uint16_t repeat_y() const { return 1; }
    virtual void set_repeat_x(uint16_t val) {}
    virtual void set_repeat_y(uint16_t val) {}
    VisualLayer layer() const { return m_layer; }
    void set_layer(VisualLayer val) { m_layer = val; }

private:
    SpritesheetID m_spr_id;
    uint16_t m_sprite;
    VisualLayer m_layer;
};

#endif /* COMPONENTS_STATIC_VISUALS_H_ */
