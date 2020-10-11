/*
 * rendering_system.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "rendering_system.h"
#include "../math_ext.h"
#include "../components/absolute_position.h"
#include "../components/null_position.h"
#include <algorithm>
#include "entity_system.h"
#include "resource_system.h"
#include "systems.h"
#include "../globals.h"
#include "../utilities.h"
#include <list>

void RenderingSystem::add_id(const EntityID entity)
{
	const int layer = system<EntitySystem>().entity_component<Visuals>(entity).layer();
	entities[layer].insert(entity);
}

void RenderingSystem::remove_id(const EntityID entity)
{
	const int layer = system<EntitySystem>().entity_component<Visuals>(entity).layer();
	entities[layer].erase(entity);
}

void RenderingSystem::set_entity_layer(const EntityID entity_id, const Visuals::VisualLayer layer)
{
	auto& visuals = system<EntitySystem>().entity_component<Visuals>(entity_id);
	if(visuals)
	{
		if(layer != visuals.layer())
		{
			remove_id(entity_id);
			visuals.set_layer(layer);
			add_id(entity_id);
		}
	}
	else
	{
		//error entity
	}
}

void RenderingSystem::update_entity_layers()
{
	std::list<EntityID> ids_to_add;

	for(int layer = 0; layer < Visuals::NUM_OF_LAYERS; ++layer)
	{
		discard_if(entities[layer],
		[&](const auto entity_id)
		{
			ids_to_add.push_back(entity_id);
			return layer != system<EntitySystem>().entity_component<Visuals>(entity_id).layer();
		});
	}

	for(const auto entity_id : ids_to_add)
		entities[system<EntitySystem>().entity_component<Visuals>(entity_id).layer()].insert(entity_id);
}

void RenderingSystem::render_entities(const Time time_diff, const bool paused, SDL_Renderer* renderer)
{
	update_entity_layers();

    //SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    const auto& screen_zone_position = system<EntitySystem>().entity_component<Position>(EntityID{0});

    const double m_screen_to_view_scale = screen_zone_position.h() ? 1.0*globals().resolution_y/screen_zone_position.h() : 1.0;

    for(auto layer = 0; layer < Visuals::NUM_OF_LAYERS; ++layer)
    {
		for(const EntityID id : entities[layer])
		{
			auto& visuals = system<EntitySystem>().entity_component<Visuals>(id);
			if(visuals)
			{
				const auto& movement = system<EntitySystem>().entity_component<Movement>(id);
				const auto& position = system<EntitySystem>().entity_component<Position>(id);
				const auto& control = system<EntitySystem>().entity_component<Control>(id);

				if(paused == false)
				{
					const auto& collision = system<EntitySystem>().entity_component<Collision>(id);
					const auto& health = system<EntitySystem>().entity_component<Health>(id);

					switch(visuals.state())
					{
						case Visuals::IDLE:
							if(health.alive() == false) visuals.set_new_state(Visuals::DEAD);
							else if(health.stunned()) visuals.set_new_state(Visuals::HIT);
							else if(control.decision_attack()) visuals.set_new_state(Visuals::ATTACK);
							else if(collision.standing_on()!=Collision::GROUND && control.decision_jump()) visuals.set_new_state(Visuals::JUMP);
							else if(collision.standing_on()==Collision::GROUND && control.decision_walk() != 0) visuals.set_new_state(Visuals::WALK);
							else if(collision.standing_on()==Collision::AIR && movement.vy() < -1) visuals.set_new_state(Visuals::FALL);
							else visuals.advance_animation(time_diff);
						break;

						case Visuals::WALK:
							if(health.alive() == false) visuals.set_new_state(Visuals::DEAD);
							else if(health.stunned()) visuals.set_new_state(Visuals::HIT);
							else if(control.decision_attack()) visuals.set_new_state(Visuals::ATTACK);
							else if(collision.standing_on()!=Collision::GROUND && control.decision_jump()) visuals.set_new_state(Visuals::JUMP);
							else if(collision.standing_on()==Collision::GROUND && control.decision_walk() == 0) visuals.set_new_state(Visuals::IDLE);
							else if(collision.standing_on()==Collision::AIR && movement.vy() < -1) visuals.set_new_state(Visuals::FALL);
							else visuals.advance_animation(time_diff);
						break;

						case Visuals::JUMP:
							if(health.alive() == false) visuals.set_new_state(Visuals::DEAD);
							else if(health.stunned()) visuals.set_new_state(Visuals::HIT);
							else if(control.decision_attack()) visuals.set_new_state(Visuals::ATTACK);
							else if(collision.standing_on()==Collision::GROUND && control.decision_walk() != 0) visuals.set_new_state(Visuals::WALK);
							else if(collision.standing_on()==Collision::GROUND && control.decision_walk() == 0) visuals.set_new_state(Visuals::IDLE);
							else if(collision.standing_on()==Collision::AIR && movement.vy() < -1 && visuals.animation_count_max()) visuals.set_new_state(Visuals::FALL);
							else visuals.advance_animation(time_diff);
						break;

						case Visuals::FALL:
							if(health.alive() == false) visuals.set_new_state(Visuals::DEAD);
							else if(health.stunned()) visuals.set_new_state(Visuals::HIT);
							else if(control.decision_attack()) visuals.set_new_state(Visuals::ATTACK);
							else if(collision.standing_on()==Collision::GROUND && control.decision_walk() != 0) visuals.set_new_state(Visuals::WALK);
							else if(collision.standing_on()==Collision::GROUND && control.decision_walk() == 0) visuals.set_new_state(Visuals::IDLE);
							else visuals.advance_animation(time_diff);
						break;

						case Visuals::ATTACK:
							if(health.alive() == false) visuals.set_new_state(Visuals::DEAD);
							else if(health.stunned()) visuals.set_new_state(Visuals::HIT);
							else if(visuals.animation_count_max() && collision.standing_on()==Collision::AIR && movement.vy() < -1) visuals.set_new_state(Visuals::FALL);
							else if(visuals.animation_count_max() && collision.standing_on()==Collision::GROUND && control.decision_jump()) visuals.set_new_state(Visuals::JUMP);
							else if(visuals.animation_count_max() && collision.standing_on()==Collision::GROUND && control.decision_walk() != 0) visuals.set_new_state(Visuals::WALK);
							else if(visuals.animation_count_max()) visuals.set_new_state(Visuals::IDLE);
							else visuals.advance_animation(time_diff);
						break;

						case Visuals::HIT:
							if(health.alive() == false) visuals.set_new_state(Visuals::DEAD);
							else if(visuals.animation_count_max() && control.decision_attack()) visuals.set_new_state(Visuals::ATTACK);
							else if(visuals.animation_count_max() && collision.standing_on()==Collision::AIR && movement.vy() < -1) visuals.set_new_state(Visuals::FALL);
							else if(visuals.animation_count_max() && collision.standing_on()==Collision::GROUND && control.decision_jump()) visuals.set_new_state(Visuals::JUMP);
							else if(visuals.animation_count_max() && collision.standing_on()==Collision::GROUND && control.decision_walk() != 0) visuals.set_new_state(Visuals::WALK);
							else if(visuals.animation_count_max() && collision.standing_on()==Collision::GROUND && control.decision_walk() == 0) visuals.set_new_state(Visuals::IDLE);
							else visuals.advance_animation(time_diff);
						break;

						case Visuals::DEAD:
							if(visuals.animation_count_max() == false)
								visuals.advance_animation(time_diff);
							//else do nothing
						break;

						default:
							visuals.advance_animation(time_diff);
						break;
					}
				}

				const optional_ref<Spritesheet> spritesheet = system<ResourceSystem>().spritesheet(visuals.spritesheet_id());
				if(spritesheet)
				{
					double scale_factor = spritesheet->scale_factor();
					const SDL_RendererFlip flip = (control.look_dir()==Control::LEFT) ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE;
					AbsolutePosition screen_pos;
					SDL_Rect dest;
					const double pos_x = position.x() + position.w()/visuals.repeat_x()/2.0 - screen_zone_position.x();
					const double pos_y = position.y() + position.h()/visuals.repeat_y()/2.0 - screen_zone_position.y();

					for(int16_t rx = 0; rx < visuals.repeat_x(); ++rx)
						for(int16_t ry = 0; ry < visuals.repeat_y(); ++ry)
						{
							const optional_ref<const Sprite> sprite = spritesheet->sprite(visuals.animation_sprite(rx, ry));
							if(sprite)
							{
								if(system<ResourceSystem>().texture(sprite->texture_id))
								{
									//TODO: to optimize and add constness
									SDL_Texture* texture = system<ResourceSystem>().texture(sprite->texture_id)->texture();
									screen_pos.set_w(sprite->clip.w*scale_factor);
									screen_pos.set_h(sprite->clip.h*scale_factor);
									screen_pos.set_x(pos_x + rx*screen_pos.w() - screen_pos.w()/2.0);
									screen_pos.set_y(pos_y + ry*screen_pos.h() - screen_pos.h()/2.0);
									dest.w = screen_pos.w()*m_screen_to_view_scale + 0.5;
									dest.h = screen_pos.h()*m_screen_to_view_scale + 0.5;
									dest.x = screen_pos.x()*m_screen_to_view_scale + 0.5;
									dest.y = globals().resolution_y - dest.h - screen_pos.y()*m_screen_to_view_scale + 0.5;

									if(objects_collide(dest.x, dest.y, dest.w, dest.h, 0, 0, globals().resolution_x, globals().resolution_y))
									{
										const int err = SDL_RenderCopyEx(renderer, texture, &sprite->clip, &dest, 0, nullptr, flip);
										if(err)
										{
											std::cerr << "Error when rendering: " << SDL_GetError() << std::endl;
										}
									}
								}
								else
								{
									//error sprite->texture_id
								}

							}
							else
							{
								//error visuals->animation_sprite(rx, ry)
							}
						}
					if(globals().show_hitboxes)
					{
						const SDL_Rect hitbox
							{ int((position.x() - screen_zone_position.x())*m_screen_to_view_scale)
							, int(globals().resolution_y + (-position.h() - position.y() + screen_zone_position.y())*m_screen_to_view_scale)
							, int(position.w()*m_screen_to_view_scale)
							, int(position.h()*m_screen_to_view_scale)
							};
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
						SDL_RenderDrawRect(renderer, &hitbox);
					}
				}
				else
				{
					//error visuals->spritesheet_id()
				}
			}
			else
			{
				//error *it
			}
    	}
    }

    SDL_RenderPresent(renderer);

}
