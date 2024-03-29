/*
 * rendering_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_RENDERING_SYSTEM_H_
#define SYSTEMS_RENDERING_SYSTEM_H_

#include "../types.h"
#include <set>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "../sdl_window.h"
#include "../math_ext.h"
#include "../components/absolute_position.h"
#include "../components/visuals_enums.h"
#include "../globals.h"
#include "../animation.h"
#include "../texture.h"

template<typename EntitySystemT, typename AnimationResourceSystemT, typename TextureResourceSystemT, typename PositionT, typename ControlT, typename VisualsT>
class RenderingSystem
{
public:
	RenderingSystem(EntitySystemT& _entity_system, AnimationResourceSystemT& _animations, TextureResourceSystemT& _textures, Globals& _globals, SdlWindow& _sdl_window)
	: entity_system{_entity_system}
	, animations{_animations}
	, textures{_textures}
	, globals{_globals}
	, sdl_window(_sdl_window)
	{}

	void add_id(const EntityID entity, const VisualLayer layer)
	{
		entities[int(layer)].insert(entity);
		entity_layer[entity] = layer;
	}

	void remove_id(const EntityID entity, const VisualLayer layer)
	{
		entities[int(layer)].erase(entity);
		entity_layer.erase(entity);
	}

	void clear()
    {
    	for(int layer = 0; layer < NUM_OF_LAYERS; ++layer)
    		entities[layer].clear();
    }

    template<typename T>
    void component_updated
	( [[maybe_unused]] const T& component
	, [[maybe_unused]] const EntityID id
	, [[maybe_unused]] const int8_t change
	)
    {
    	if constexpr(std::is_same<T, VisualsT>::value)
		{
			//1 = find=end
			//0 = find!=end layer=layer
			//-1 = find!=end layer!=layer
			const int8_t layer_change = entity_layer.find(id) == cend(entity_layer) ? 1 : -(component.layer() != entity_layer[id]);

			if(change < 0 || layer_change < 0)
				remove_id(id, entity_layer[id]);
			if(change > 0 || layer_change != 0)
				add_id(id, component.layer());
		}
    }

    void update(const Time time_diff)
    {
    	SDL_Renderer* renderer = &sdl_window.renderer();
        SDL_SetRenderDrawColor
		( renderer
		, globals(Globals::app_background_r).integer()
		, globals(Globals::app_background_g).integer()
		, globals(Globals::app_background_b).integer()
		, globals(Globals::app_background_a).integer()
		);
        SDL_RenderClear(renderer);

        const auto& screen_zone_position = entity_system.template entity_component<PositionT>(EntityID{0});

        const double m_screen_to_view_scale = screen_zone_position.h() ? 1.0*sdl_window.res_height()/screen_zone_position.h() : 1.0;

        for(auto layer = 0; layer < NUM_OF_LAYERS; ++layer)
        {
    		for(const EntityID id : entities[layer])
    		{
    			auto& visuals = entity_system.template entity_component<VisualsT>(id);
    			if(visuals)
    			{
    				const auto& position = entity_system.template entity_component<PositionT>(id);

					if(globals(Globals::app_paused).integer() == false)
    					visuals.update_animation(time_diff);

					const SDL_RendererFlip flip = (visuals.look_dir_x() < 0.0) ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE;
					const double pos_x = position.x() + position.w()/visuals.repeat_x()/2.0 - screen_zone_position.x();
					const double pos_y = position.y() + position.h()/visuals.repeat_y()/2.0 - screen_zone_position.y();

					for(int16_t rx = 0; rx < visuals.repeat_x(); ++rx)
						for(int16_t ry = 0; ry < visuals.repeat_y(); ++ry)
						{
							const auto animation_frame = visuals.animation_frame(rx, ry);
							const optional_ref<Animation> anim_opt = animations[animation_frame.id];
							if(anim_opt)
							{
								const optional_ref<Sprite> sprite_opt = anim_opt->get().sprite(animation_frame.frame);
								if(sprite_opt)
								{
									const double scale_factor = anim_opt->get().scale_factor();
									AbsolutePosition screen_pos;
									screen_pos.set_w(sprite_opt->get().clip.w*scale_factor);
									screen_pos.set_h(sprite_opt->get().clip.h*scale_factor);
									screen_pos.set_x(pos_x + rx*screen_pos.w() - screen_pos.w()/2.0);
									screen_pos.set_y(pos_y + ry*screen_pos.h() - screen_pos.h()/2.0);
									SDL_Rect dest;
									dest.w = int(screen_pos.w()*m_screen_to_view_scale + 0.5);
									dest.h = int(screen_pos.h()*m_screen_to_view_scale + 0.5);
									dest.x = int(screen_pos.x()*m_screen_to_view_scale + 0.5);
									dest.y = int(sdl_window.res_height() - dest.h - screen_pos.y()*m_screen_to_view_scale + 0.5);

									if(objects_collide(dest.x, dest.y, dest.w, dest.h, 0, 0, sdl_window.res_width(), sdl_window.res_height()))
									{
										const optional_ref<Texture> texture_opt = textures[sprite_opt->get().texture_id];
										if(texture_opt)
										{
											SDL_Texture* texture = texture_opt->get().texture();
											const int err = SDL_RenderCopyEx(renderer, texture, &sprite_opt->get().clip, &dest, 0, nullptr, flip);
											if(err)
											{
												std::cerr << "Error when rendering: " << SDL_GetError() << std::endl;
											}
										}
										else
										{
											//error sprite->texture_id
										}
									}

								}
								else
								{
									//error animation_frame.frame
								}
							}
							else
							{
								//error animation_frame.id
							}
						}
    			}
    			else
    			{
    				//error *it
    			}
        	}
        }

		if(globals(Globals::app_show_hitboxes).integer())
		{
			for(auto layer = 0; layer < NUM_OF_LAYERS; ++layer)
			{
				for(const EntityID id : entities[layer])
				{
					const auto& position = entity_system.template entity_component<PositionT>(id);

					const SDL_Rect hitbox
						{ int((position.x() - screen_zone_position.x())*m_screen_to_view_scale)
						, int(sdl_window.res_height() + (-position.h() - position.y() + screen_zone_position.y())*m_screen_to_view_scale)
						, int(position.w()*m_screen_to_view_scale)
						, int(position.h()*m_screen_to_view_scale)
						};
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					SDL_RenderDrawRect(renderer, &hitbox);
				}
			}
		}

        SDL_RenderPresent(renderer);

    }

    SDL_Renderer& renderer() { return sdl_window.renderer(); }

protected:
    EntitySystemT& entity_system;
    AnimationResourceSystemT& animations;
    TextureResourceSystemT& textures;
    Globals& globals;
    SdlWindow& sdl_window;
    std::set<EntityID> entities[NUM_OF_LAYERS];
    std::unordered_map<EntityID, VisualLayer> entity_layer;
};

#endif /* SYSTEMS_RENDERING_SYSTEM_H_ */
