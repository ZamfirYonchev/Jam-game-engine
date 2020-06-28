/*
 * tiled_visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_TILED_VISUALS_H_
#define COMPONENTS_TILED_VISUALS_H_

#include "visuals.h"

class TiledVisuals : public Visuals
{
public:
    TiledVisuals(SpritesheetID spr_id, uint16_t repeat_x, uint16_t repeat_y)
    : m_spritesheet_id(spr_id)
    , m_repeat_x(repeat_x)
    , m_repeat_y(repeat_y)
    , m_layer(ACTION)
    {}

    TiledVisuals() : TiledVisuals(-1, 0, 0) {}

    void print(std::ostream& to) const
    {
    	to << "UseTiledVisuals "
    	   << m_spritesheet_id << " "
    	   << m_repeat_x << " "
    	   << m_repeat_y << " ";
    }

    RenderStates state() const { return IDLE; }
    void set_new_state(RenderStates new_state) {}
    void advance_animation(Time time_diff) {}
    bool animation_count_max() const { return 0; }

    uint8_t animation_sprite(uint16_t rx, uint16_t ry) const
    {
    	return (rx > 0) * (1 + (rx==(repeat_x()-1))) + 3*((ry > 0) * (1 + (ry==(repeat_y()-1))));
    }

    SpritesheetID spritesheet_id() { return m_spritesheet_id; }
    void set_spritesheet_id(SpritesheetID spr_id) { m_spritesheet_id = spr_id; }

    uint16_t repeat_x() const { return m_repeat_x; }
    uint16_t repeat_y() const { return m_repeat_y; }
    void set_repeat_x(uint16_t val) { m_repeat_x = val; }
    void set_repeat_y(uint16_t val) { m_repeat_y = val; }
    VisualLayer layer() const { return m_layer; }
    void set_layer(VisualLayer val) { m_layer = val; }

private:
    SpritesheetID m_spritesheet_id;
    uint16_t m_repeat_x, m_repeat_y;
    VisualLayer m_layer;
};

#endif /* COMPONENTS_TILED_VISUALS_H_ */
