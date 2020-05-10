/*
 * rendering_system.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#include "rendering_system.h"
#include "../globals.h"
#include "../math_ext.h"

void RenderingSystem::add_id(EntityID entity)
{
	if(globals.entity_system.entity(entity))
	{
		int layer = globals.entity_system.entity(entity)->visuals()->layer();
	    for(auto it = entities[layer].begin(); it != entities[layer].end(); ++it)
	        if((*it) == entity)
	        	return;

	    entities[layer].push_back(entity);
	}
	else
	{
		//error entity
	}
}

void RenderingSystem::remove_id(EntityID entity)
{
	if(globals.entity_system.entity(entity))
	{
		int layer = globals.entity_system.entity(entity)->visuals()->layer();
		for(auto it = entities[layer].begin(); it != entities[layer].end(); ++it)
			if((*it) == entity)
			{
				entities[layer].erase(it);
				break;
			}
	}
	else
	{
		//error entity
	}
}

void RenderingSystem::set_entity_layer(EntityID entity_id, Visuals::VisualLayer layer)
{
	if(globals.entity_system.entity(entity_id))
	{
		Visuals* visuals = globals.entity_system.entity(entity_id)->visuals();
		if(layer != visuals->layer())
		{
			remove_id(entity_id);
			visuals->set_layer(layer);
			add_id(entity_id);
		}
	}
	else
	{
		//error entity
	}
}

void RenderingSystem::render_entities(Time time_diff, bool paused, SDL_Renderer* renderer) const
{
    //SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    Position* screen_zone_position;
    if(globals.entity_system.entity(0))
    	screen_zone_position = globals.entity_system.entity(0)->position();
    else
    	screen_zone_position = Position::null;

    for(auto layer = 0; layer < Visuals::NUM_OF_LAYERS; ++layer)
    {
		for(auto it = entities[layer].begin(); it != entities[layer].end(); ++it)
		{
			if(globals.entity_system.entity(*it))
			{
				Entity& entity = *(globals.entity_system.entity(*it));
				Visuals* visuals = entity.visuals();
				Movement* movement = entity.movement();
				Position* position = entity.position();
				Control* control = entity.control();

				if(paused == false)
				{
					Collision* collision = entity.collision();
					Health* health = entity.health();

					switch(visuals->state())
					{
						case Visuals::IDLE:
							if(health->alive() == false) visuals->set_new_state(Visuals::DEAD);
							else if(health->stunned()) visuals->set_new_state(Visuals::HIT);
							else if(control->decision_attack()) visuals->set_new_state(Visuals::ATTACK);
							else if(collision->standing_on()!=Collision::GROUND && control->decision_jump()) visuals->set_new_state(Visuals::JUMP);
							else if(collision->standing_on()==Collision::GROUND && control->decision_walk() != 0) visuals->set_new_state(Visuals::WALK);
							else if(collision->standing_on()==Collision::AIR && movement->vy() < -1) visuals->set_new_state(Visuals::FALL);
							else visuals->advance_animation(time_diff);
						break;

						case Visuals::WALK:
							if(health->alive() == false) visuals->set_new_state(Visuals::DEAD);
							else if(health->stunned()) visuals->set_new_state(Visuals::HIT);
							else if(control->decision_attack()) visuals->set_new_state(Visuals::ATTACK);
							else if(collision->standing_on()!=Collision::GROUND && control->decision_jump()) visuals->set_new_state(Visuals::JUMP);
							else if(collision->standing_on()==Collision::GROUND && control->decision_walk() == 0) visuals->set_new_state(Visuals::IDLE);
							else if(collision->standing_on()==Collision::AIR && movement->vy() < -1) visuals->set_new_state(Visuals::FALL);
							else visuals->advance_animation(time_diff);
						break;

						case Visuals::JUMP:
							if(health->alive() == false) visuals->set_new_state(Visuals::DEAD);
							else if(health->stunned()) visuals->set_new_state(Visuals::HIT);
							else if(control->decision_attack()) visuals->set_new_state(Visuals::ATTACK);
							else if(collision->standing_on()==Collision::GROUND && control->decision_walk() != 0) visuals->set_new_state(Visuals::WALK);
							else if(collision->standing_on()==Collision::GROUND && control->decision_walk() == 0) visuals->set_new_state(Visuals::IDLE);
							else if(collision->standing_on()==Collision::AIR && movement->vy() < -1 && visuals->animation_count_max()) visuals->set_new_state(Visuals::FALL);
							else visuals->advance_animation(time_diff);
						break;

						case Visuals::FALL:
							if(health->alive() == false) visuals->set_new_state(Visuals::DEAD);
							else if(health->stunned()) visuals->set_new_state(Visuals::HIT);
							else if(control->decision_attack()) visuals->set_new_state(Visuals::ATTACK);
							else if(collision->standing_on()==Collision::GROUND && control->decision_walk() != 0) visuals->set_new_state(Visuals::WALK);
							else if(collision->standing_on()==Collision::GROUND && control->decision_walk() == 0) visuals->set_new_state(Visuals::IDLE);
							else visuals->advance_animation(time_diff);
						break;

						case Visuals::ATTACK:
							if(health->alive() == false) visuals->set_new_state(Visuals::DEAD);
							else if(health->stunned()) visuals->set_new_state(Visuals::HIT);
							else if(visuals->animation_count_max() && collision->standing_on()==Collision::AIR && movement->vy() < -1) visuals->set_new_state(Visuals::FALL);
							else if(visuals->animation_count_max() && collision->standing_on()==Collision::GROUND && control->decision_jump()) visuals->set_new_state(Visuals::JUMP);
							else if(visuals->animation_count_max() && collision->standing_on()==Collision::GROUND && control->decision_walk() != 0) visuals->set_new_state(Visuals::WALK);
							else if(visuals->animation_count_max()) visuals->set_new_state(Visuals::IDLE);
							else visuals->advance_animation(time_diff);
						break;

						case Visuals::HIT:
							if(health->alive() == false) visuals->set_new_state(Visuals::DEAD);
							else if(visuals->animation_count_max() && control->decision_attack()) visuals->set_new_state(Visuals::ATTACK);
							else if(visuals->animation_count_max() && collision->standing_on()==Collision::AIR && movement->vy() < -1) visuals->set_new_state(Visuals::FALL);
							else if(visuals->animation_count_max() && collision->standing_on()==Collision::GROUND && control->decision_jump()) visuals->set_new_state(Visuals::JUMP);
							else if(visuals->animation_count_max() && collision->standing_on()==Collision::GROUND && control->decision_walk() != 0) visuals->set_new_state(Visuals::WALK);
							else if(visuals->animation_count_max() && collision->standing_on()==Collision::GROUND && control->decision_walk() == 0) visuals->set_new_state(Visuals::IDLE);
							else visuals->advance_animation(time_diff);
						break;

						case Visuals::DEAD:
							if(visuals->animation_count_max() == false)
								visuals->advance_animation(time_diff);
							//else do nothing
						break;

						default:
							visuals->advance_animation(time_diff);
						break;
					}
				}

				optional_ref<Spritesheet> spritesheet = globals.resource_system.spritesheet(visuals->spritesheet_id());
				if(spritesheet)
				{
					double scale_factor = spritesheet->scale_factor();
					SDL_RendererFlip flip = (control->look_dir()==Control::LEFT) ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE;
					SDL_Texture* texture = nullptr;
					SDL_Rect dest;

					for(int16_t rx = 0; rx < visuals->repeat_x(); ++rx)
						for(int16_t ry = 0; ry < visuals->repeat_y(); ++ry)
						{
							optional_ref<Sprite> sprite = spritesheet->sprite(visuals->animation_sprite(rx, ry));
							if(sprite)
							{
								if(globals.resource_system.texture(sprite->texture_id))
								{
									texture = globals.resource_system.texture(sprite->texture_id)->texture();
									dest.w = sprite->clip.w*scale_factor;
									dest.h = sprite->clip.h*scale_factor;
									dest.x = position->x() + position->w()/visuals->repeat_x()/2.0 - dest.w/2.0 + rx*dest.w - screen_zone_position->x();
									dest.y = globals.resolution_y - dest.h - (position->y() + position->h()/visuals->repeat_y()/2.0 - dest.h/2.0 + ry*dest.h  - screen_zone_position->y());

									if(objects_collide(dest.x, dest.y, dest.w, dest.h, 0, 0, globals.resolution_x, globals.resolution_y))
									{
										int err = SDL_RenderCopyEx(renderer, texture, &sprite->clip, &dest, 0, nullptr, flip);
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
					if(globals.show_hitboxes)
					{
						SDL_Rect hitbox
							{ int(entity.position()->x() - screen_zone_position->x())
							, int(globals.resolution_y-entity.position()->h() - entity.position()->y() + screen_zone_position->y())
							, int(entity.position()->w())
							, int(entity.position()->h())
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
