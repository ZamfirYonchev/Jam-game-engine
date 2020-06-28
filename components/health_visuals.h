/*
 * character_health_visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_HEALTH_VISUALS_H_
#define COMPONENTS_HEALTH_VISUALS_H_

#include "visuals.h"

class HealthVisuals : public Visuals
{
public:
	HealthVisuals(EntityID self_id, SpritesheetID spr_id, uint16_t repeat_x)
	: m_self_id(self_id)
	, m_spr_id(spr_id)
	, m_repeat_x(repeat_x)
	{}

	HealthVisuals() : HealthVisuals(-1, -1, 0) {}

    void print(std::ostream& to) const
    {
    	to << "UseHealthVisuals "
    	   << m_spr_id << " "
		   << m_repeat_x << " ";
    }

	RenderStates state() const { return IDLE; }
    void set_new_state(RenderStates new_state) {}
    void advance_animation(Time time_diff) {}
    uint8_t animation_sprite(uint16_t rx, uint16_t ry) const;
    bool animation_count_max() const { return true; }
    SpritesheetID spritesheet_id() { return m_spr_id; }
    void set_spritesheet_id(SpritesheetID spr_id) { m_spr_id = spr_id; }
    uint16_t repeat_x() const { return m_repeat_x; }
    virtual uint16_t repeat_y() const { return 1; }
    virtual void set_repeat_x(uint16_t val) { m_repeat_x = val; }
    virtual void set_repeat_y(uint16_t val) {}
    VisualLayer layer() const { return CLOSE_BACKGROUND; }
    void set_layer(VisualLayer val) {}

private:
    EntityID m_self_id;
    SpritesheetID m_spr_id;
    uint16_t m_repeat_x;
};

#endif /* COMPONENTS_HEALTH_VISUALS_H_ */
