/*
 * animation.h
 *
 *  Created on: Jan 17, 2021
 *      Author: zamfi
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "sprite.h"
#include <vector>
#include "types.h"

class ResourceSystem;

class Animation
{
public:
	Animation(const int frame_delay_ms, const double scale_factor)
	: m_sprites{}
	, m_frame_delay(frame_delay_ms)
    , m_scale_factor(scale_factor)
    {}

    Animation() : Animation(50, 1.0) {}

    int add_sprite(const Sprite& sprite)
    {
    	const int sprite_id = m_sprites.size();
    	m_sprites.push_back(sprite);
    	return sprite_id;
    }

    optional_ref<Sprite> sprite(const int index)
    {
    	if(0 <= index && index < int(m_sprites.size()))
            return optional_ref<Sprite>{m_sprites[index]};
    	else
    		return {};
    }

    int frame_count() const { return m_sprites.size(); }

    void set_scale_factor(const double scale) { m_scale_factor = scale; }
    double scale_factor() const { return m_scale_factor; }

    void set_frame_delay_ms(const int value) { m_frame_delay = value; }
    int frame_delay_ms() const { return m_frame_delay; }

private:
    std::vector<Sprite> m_sprites;
    int m_frame_delay;
    double m_scale_factor;
};

#endif /* ANIMATION_H_ */
