/*
 * tiled_visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_TILED_VISUALS_H_
#define COMPONENTS_TILED_VISUALS_H_

#include "visuals.h"
#include "../types.h"
#include "../math_ext.h"
#include "position.h"

template<typename EntitySystemT>
class TiledVisuals : public Visuals
{
public:
	using Base = Visuals;
    TiledVisuals(SpritesheetID spr_id, double tile_w, double tile_h, EntityID self_id, EntitySystemT& entity_system)
    : m_self_id(self_id)
    , m_spritesheet_id(spr_id)
    , m_tile_w(tile_w)
    , m_tile_h(tile_h)
	, m_layer(VisualLayer::ACTION)
	, m_entity_system(entity_system)
    {}

    void print(std::ostream& to) const
    {
    	to << "UseTiledVisuals "
    	   << m_spritesheet_id << " "
    	   << m_tile_w << " "
    	   << m_tile_h << " ";
    }

    void update_animation(const Time time_diff) {}

    uint8_t animation_sprite(uint16_t rx, uint16_t ry) const
    {
    	return (rx > 0) * (1 + (rx==(repeat_x()-1))) + 3*((ry > 0) * (1 + (ry==(repeat_y()-1))));
    }

    SpritesheetID spritesheet_id() { return m_spritesheet_id; }
    void set_spritesheet_id(SpritesheetID spr_id) { m_spritesheet_id = spr_id; }

    uint16_t repeat_x() const
    {
    	return std::ceil(m_entity_system.entity_component(m_self_id, (Position*)nullptr).w()/m_tile_w);
    }

    uint16_t repeat_y() const
    {
    	return std::ceil(m_entity_system.entity_component(m_self_id, (Position*)nullptr).h()/m_tile_h);
    }

    void set_repeat_x(uint16_t val)
    {
    	m_tile_w = m_entity_system.entity_component(m_self_id, (Position*)nullptr).w()/val;
    }

    void set_repeat_y(uint16_t val)
    {
    	m_tile_h = m_entity_system.entity_component(m_self_id, (Position*)nullptr).h()/val;
    }

    VisualLayer layer() const { return m_layer; }
    void set_layer(VisualLayer val) { m_layer = val; }

    EntityID m_self_id;

private:
    SpritesheetID m_spritesheet_id;
    double m_tile_w, m_tile_h;
    VisualLayer m_layer;
    EntitySystemT& m_entity_system;
};

#endif /* COMPONENTS_TILED_VISUALS_H_ */
