/*
 * menu_item_visuals.h
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_MENU_ITEM_VISUALS_H_
#define COMPONENTS_MENU_ITEM_VISUALS_H_

#include "visuals.h"
#include "control.h"

template<typename EntitySystemT>
class MenuItemVisuals : public Visuals
{
public:
	using Base = Visuals;
	MenuItemVisuals(EntityID self_id, SpritesheetID spr_id, EntitySystemT& entity_system)
	: m_self_id(self_id)
	, m_spr_id(spr_id)
	, m_entity_system(entity_system)
	{}

    void print(std::ostream& to) const
    {
    	to << "UseMenuItemVisuals "
    	   << m_spr_id << " ";
    }

    void update_animation(const Time time_diff) {}

    uint8_t animation_sprite(uint16_t rx, uint16_t ry) const
    {
    	const auto& control = m_entity_system.entity_component(m_self_id, (Control*)nullptr);
    	return control.decision_attack() ? 2 : (control.decision_vertical() != 0) ? 1 : 0;
    }

    SpritesheetID spritesheet_id() { return m_spr_id; }
    void set_spritesheet_id(SpritesheetID spr_id) { m_spr_id = spr_id; }
    uint16_t repeat_x() const { return 1; }
    uint16_t repeat_y() const { return 1; }
    void set_repeat_x(uint16_t val) {}
    void set_repeat_y(uint16_t val) {}
    VisualLayer layer() const { return VisualLayer::FOREGROUND; }
    void set_layer(VisualLayer val) {}

    EntityID m_self_id;

private:
    SpritesheetID m_spr_id;
    EntitySystemT& m_entity_system;
};

#endif /* COMPONENTS_MENU_ITEM_VISUALS_H_ */
