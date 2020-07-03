/*
 * menu_item_visuals.h
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_MENU_ITEM_VISUALS_H_
#define COMPONENTS_MENU_ITEM_VISUALS_H_

#include "visuals.h"

class MenuItemVisuals : public Visuals
{
public:
	using Base = Visuals;
	MenuItemVisuals(SpritesheetID spr_id, EntityID self_id)
	: m_spr_id(spr_id)
	, m_self_id(self_id)
	{}

    void print(std::ostream& to) const
    {
    	to << "UseMenuItemVisuals "
    	   << m_spr_id << " ";
    }

    RenderStates state() const { return IDLE; }
    void set_new_state(RenderStates new_state) {}
    void advance_animation(int32_t time_diff) {}
    uint8_t animation_sprite(uint16_t rx, uint16_t ry) const;
    bool animation_count_max() const { return true; }
    SpritesheetID spritesheet_id() { return m_spr_id; }
    void set_spritesheet_id(SpritesheetID spr_id) { m_spr_id = spr_id; }
    uint16_t repeat_x() const { return 1; }
    uint16_t repeat_y() const { return 1; }
    void set_repeat_x(uint16_t val) {}
    void set_repeat_y(uint16_t val) {}
    VisualLayer layer() const { return FOREGROUND; }
    void set_layer(VisualLayer val) {}

private:
    SpritesheetID m_spr_id;
    EntityID m_self_id;
};

#endif /* COMPONENTS_MENU_ITEM_VISUALS_H_ */
