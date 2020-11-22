/*
 * character_health_visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_HEALTH_VISUALS_H_
#define COMPONENTS_HEALTH_VISUALS_H_

#include "visuals.h"
#include "health.h"

template<typename EntitySystemT>
class HealthVisuals : public Visuals
{
public:
	using Base = Visuals;
	HealthVisuals(EntityID self_id, SpritesheetID spr_id, uint16_t repeat_x, EntitySystemT& entity_system)
	: m_self_id(self_id)
	, m_spr_id(spr_id)
	, m_repeat_x(repeat_x)
	, m_entity_system(entity_system)
	{}

    void print(std::ostream& to) const
    {
    	to << "UseHealthVisuals "
    	   << m_spr_id << " "
		   << m_repeat_x << " ";
    }

    void update_animation(const Time time_diff) {}

    uint8_t animation_sprite(uint16_t rx, uint16_t ry) const
    {
    	const auto& health = m_entity_system.entity_component(m_self_id, (Health*)nullptr);
    	return (m_repeat_x != 0) && (health.max_hp() != 0) && (1.0*rx/m_repeat_x) < (1.0*health.hp()/health.max_hp());
    }

    SpritesheetID spritesheet_id() { return m_spr_id; }
    void set_spritesheet_id(SpritesheetID spr_id) { m_spr_id = spr_id; }
    uint16_t repeat_x() const { return m_repeat_x; }
    virtual uint16_t repeat_y() const { return 1; }
    virtual void set_repeat_x(uint16_t val) { m_repeat_x = val; }
    virtual void set_repeat_y(uint16_t val) {}
    VisualLayer layer() const { return VisualLayer::CLOSE_BACKGROUND; }
    void set_layer(VisualLayer val) {}

    EntityID m_self_id;

private:
    SpritesheetID m_spr_id;
    uint16_t m_repeat_x;
    EntitySystemT& m_entity_system;
};

#endif /* COMPONENTS_HEALTH_VISUALS_H_ */
