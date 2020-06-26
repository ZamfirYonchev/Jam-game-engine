/*
 * rendering_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_RENDERING_SYSTEM_H_
#define SYSTEMS_RENDERING_SYSTEM_H_

#include "../types.h"
#include <list>
#include "../components/visuals.h"
#include <SDL2/SDL.h>

class RenderingSystem
{
public:
	RenderingSystem() : m_screen_to_view_scale(1) {}
    void add_id(EntityID entity);
    void remove_id(EntityID entity);
    void clear()
    {
    	for(int layer = 0; layer < Visuals::NUM_OF_LAYERS; ++layer)
    		entities[layer].clear();
    }

    void set_entity_layer(EntityID entity, Visuals::VisualLayer layer);
    void render_entities(const Time time_diff, const bool paused, SDL_Renderer* renderer) const;

protected:
    std::list<EntityID> entities[Visuals::NUM_OF_LAYERS];
    mutable double m_screen_to_view_scale;
};

#endif /* SYSTEMS_RENDERING_SYSTEM_H_ */
