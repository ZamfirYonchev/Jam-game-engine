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
	int layer = globals.entity_system.entity(entity)->visuals()->layer();
    for(auto it = entities[layer].begin(); it != entities[layer].end(); ++it)
        if((*it) == entity)
        	return;

    entities[layer].push_back(entity);
}

void RenderingSystem::remove_id(EntityID entity)
{
	int layer = globals.entity_system.entity(entity)->visuals()->layer();
    for(auto it = entities[layer].begin(); it != entities[layer].end(); ++it)
        if((*it) == entity)
        {
            entities[layer].erase(it);
            break;
        }
}

void RenderingSystem::set_entity_layer(EntityID entity, Visuals::VisualLayer layer)
{
	if(layer != globals.entity_system.entity(entity)->visuals()->layer())
	{
		remove_id(entity);
		globals.entity_system.entity(entity)->visuals()->set_layer(layer);
		add_id(entity);
	}
}

void RenderingSystem::render_entities(Time time_diff, bool paused, SDL_Renderer* renderer) const
{
    //SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    Position* screen_zone_position;
    if(globals.entity_system.entity(0) == nullptr)
    	screen_zone_position = Position::null;
    else
    	screen_zone_position = globals.entity_system.entity(0)->position();

    for(auto layer = 0; layer < Visuals::NUM_OF_LAYERS; ++layer)
    {
		for(auto it = entities[layer].begin(); it != entities[layer].end(); ++it)
		{
			Visuals* visuals = globals.entity_system.entity(*it)->visuals();
			Movement* movement = globals.entity_system.entity(*it)->movement();
			Position* position = globals.entity_system.entity(*it)->position();
			Control* control = globals.entity_system.entity(*it)->control();

			if(paused == false)
			{
				Collision* collision = globals.entity_system.entity(*it)->collision();
				Health* health = globals.entity_system.entity(*it)->health();

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

			Spritesheet* spritesheet = globals.resource_system.spritesheet(visuals->spritesheet_id());
			assert(spritesheet); //to check that spritesheet is correct
			double scale_factor = spritesheet->scale_factor();
			SDL_RendererFlip flip = (control->look_dir()==Control::LEFT) ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE;
			Sprite* sprite = nullptr;
			SDL_Texture* texture = nullptr;
			SDL_Rect dest;

			for(int16_t rx = 0; rx < visuals->repeat_x(); ++rx)
				for(int16_t ry = 0; ry < visuals->repeat_y(); ++ry)
				{
					sprite = spritesheet->sprite(visuals->animation_sprite(rx, ry));
					assert(sprite); //to check that animation count is correct
					texture = globals.resource_system.texture(sprite->texture_id)->texture();
					assert(texture); //to check that sprite is correct

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
			if(globals.show_hitboxes)
			{
				SDL_Rect hitbox
					{ int(globals.entity_system.entity(*it)->position()->x() - screen_zone_position->x())
					, int(globals.resolution_y-globals.entity_system.entity(*it)->position()->h() - globals.entity_system.entity(*it)->position()->y() + screen_zone_position->y())
					, int(globals.entity_system.entity(*it)->position()->w())
					, int(globals.entity_system.entity(*it)->position()->h())
					};
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &hitbox);
			}

		}
    }

    SDL_RenderPresent(renderer);

}
