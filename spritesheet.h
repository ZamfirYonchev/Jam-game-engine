/*
 * spritesheet.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SPRITESHEET_H_
#define SPRITESHEET_H_

#include "sprite.h"
#include <vector>
#include "types.h"

class ResourceSystem;

class Spritesheet
{
public:
    Spritesheet(const uint8_t idle_start
			  , const uint8_t idle_size
			  , const uint8_t walk_start
			  , const uint8_t walk_size
			  , const uint8_t jump_start
			  , const uint8_t jump_size
			  , const uint8_t fall_start
			  , const uint8_t fall_size
			  , const uint8_t attack_start
			  , const uint8_t attack_size
			  , const uint8_t hit_start
			  , const uint8_t hit_size
			  , const uint8_t dead_start
			  , const uint8_t dead_size
			  , const double scale_factor
			  )
	: m_sprites()
    , m_idle_sprite_start(idle_start)
    , m_idle_sprite_size(idle_size)
    , m_walk_sprite_start(walk_start)
    , m_walk_sprite_size(walk_size)
    , m_jump_sprite_start(jump_start)
    , m_jump_sprite_size(jump_size)
    , m_fall_sprite_start(fall_start)
    , m_fall_sprite_size(fall_size)
	, m_attack_sprite_start(attack_start)
	, m_attack_sprite_size(attack_size)
	, m_hit_sprite_start(hit_start)
	, m_hit_sprite_size(hit_size)
    , m_dead_sprite_start(dead_start)
    , m_dead_sprite_size(dead_size)
    , m_scale_factor(scale_factor)
    {}

    Spritesheet()
    : Spritesheet(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.0)
    {}

    int add_sprite(const TextureID tex_index, const int x, const int y, const int w, const int h)
    {
    	const int sprite_id = m_sprites.size();
    	m_sprites.push_back({tex_index, {x, y, w, h}});
    	return sprite_id;
    }

    optional_ref<Sprite> sprite(const unsigned int index)
    {
    	if(index < m_sprites.size())
            return optional_ref<Sprite>{m_sprites[index]};
    	else
    		return {};
    }

    void set_scale_factor(const double scale)
    {
        m_scale_factor = scale;
    }

    double scale_factor() const { return m_scale_factor; }

    void set_idle_sprite_start(const unsigned int val) { m_idle_sprite_start = val; }
    void set_idle_sprite_size (const unsigned int val) { m_idle_sprite_size = val; }
    void set_walk_sprite_start(const unsigned int val) { m_walk_sprite_start = val; }
    void set_walk_sprite_size (const unsigned int val) { m_walk_sprite_size = val; }
    void set_jump_sprite_start(const unsigned int val) { m_jump_sprite_start = val; }
    void set_jump_sprite_size (const unsigned int val) { m_jump_sprite_size = val; }
    void set_fall_sprite_start(const unsigned int val) { m_fall_sprite_start = val; }
    void set_fall_sprite_size (const unsigned int val) { m_fall_sprite_size = val; }
    void set_attack_sprite_start(const unsigned int val){ m_attack_sprite_start = val; }
    void set_attack_sprite_size (const unsigned int val){ m_attack_sprite_size = val; }
    void set_hit_sprite_start(const unsigned int val) { m_hit_sprite_start = val; }
    void set_hit_sprite_size (const unsigned int val) { m_hit_sprite_size = val; }
    void set_dead_sprite_start(const unsigned int val) { m_dead_sprite_start = val; }
    void set_dead_sprite_size (const unsigned int val) { m_dead_sprite_size = val; }

    unsigned int idle_sprite_start()const { return m_idle_sprite_start; }
    unsigned int idle_sprite_size ()const { return m_idle_sprite_size; }
    unsigned int walk_sprite_start()const { return m_walk_sprite_start; }
    unsigned int walk_sprite_size ()const { return m_walk_sprite_size; }
    unsigned int jump_sprite_start()const { return m_jump_sprite_start; }
    unsigned int jump_sprite_size ()const { return m_jump_sprite_size; }
    unsigned int fall_sprite_start()const { return m_fall_sprite_start; }
    unsigned int fall_sprite_size ()const { return m_fall_sprite_size; }
    unsigned int attack_sprite_start()const{ return m_attack_sprite_start; }
    unsigned int attack_sprite_size ()const{ return m_attack_sprite_size; }
    unsigned int hit_sprite_start()const { return m_hit_sprite_start; }
    unsigned int hit_sprite_size ()const { return m_hit_sprite_size; }
    unsigned int dead_sprite_start()const { return m_dead_sprite_start; }
    unsigned int dead_sprite_size ()const { return m_dead_sprite_size; }

private:
    std::vector<Sprite> m_sprites;

    unsigned int m_idle_sprite_start;
    unsigned int m_idle_sprite_size;
    unsigned int m_walk_sprite_start;
    unsigned int m_walk_sprite_size;
    unsigned int m_jump_sprite_start;
    unsigned int m_jump_sprite_size;
    unsigned int m_fall_sprite_start;
    unsigned int m_fall_sprite_size;
    unsigned int m_attack_sprite_start;
    unsigned int m_attack_sprite_size;
    unsigned int m_hit_sprite_start;
    unsigned int m_hit_sprite_size;
    unsigned int m_dead_sprite_start;
    unsigned int m_dead_sprite_size;
    double m_scale_factor;
};



#endif /* SPRITESHEET_H_ */
