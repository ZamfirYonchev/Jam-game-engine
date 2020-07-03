/*
 * character_visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_CHARACTER_VISUALS_H_
#define COMPONENTS_CHARACTER_VISUALS_H_

#include "visuals.h"

class CharacterVisuals : public Visuals
{
public:
	using Base = Visuals;
    static const unsigned int ANIMATION_DELAY_MS = 50;

    CharacterVisuals(SpritesheetID spr_id)
    : m_current_state(IDLE)
    , m_animation_count(0)
    , m_animation_time(0)
    , m_spritesheet_id(spr_id)
    , m_layer(ACTION)
    {}

    CharacterVisuals() : CharacterVisuals(-1) {}
    ~CharacterVisuals() {}

    void print(std::ostream& to) const
    {
    	to << "UseCharacterVisuals "
    	   << m_spritesheet_id<< " ";
    }

    RenderStates state() const { return m_current_state; }
    void set_new_state(RenderStates new_state)
    {
        m_current_state = new_state;
        m_animation_count = 0;
        m_animation_time = 0;
    }

    void advance_animation(Time time_diff)
    {
        m_animation_time += time_diff;
        if(m_animation_time >= ANIMATION_DELAY_MS)
        {
            m_animation_time -= ANIMATION_DELAY_MS;
    		m_animation_count = (m_animation_count+1)%animation_state_size();
        }
    }

    bool animation_count_max() const
    {
        return (m_animation_count == animation_state_size()-1);
    }

    uint8_t animation_sprite(uint16_t rx, uint16_t ry) const
    {
        return m_animation_count + animation_state_offset();
    }

    SpritesheetID spritesheet_id() { return m_spritesheet_id; }
    void set_spritesheet_id(SpritesheetID spr_id) { m_spritesheet_id = spr_id; }

    uint16_t repeat_x() const { return 1; }
    uint16_t repeat_y() const { return 1; }
    void set_repeat_x(uint16_t val) {}
    void set_repeat_y(uint16_t val) {}
    VisualLayer layer() const { return m_layer; }
    void set_layer(VisualLayer val) { m_layer = val; }

private:
    uint8_t animation_state_offset() const;
    uint8_t animation_state_size() const;

    RenderStates m_current_state;
    unsigned int m_animation_count;
    double m_animation_time;
    SpritesheetID m_spritesheet_id;
    VisualLayer m_layer;
};

#endif /* COMPONENTS_CHARACTER_VISUALS_H_ */
