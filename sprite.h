/*
 * sprite.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL2/SDL.h>
#include "types.h"

struct Sprite
{
    Sprite(TextureID texture_id, const SDL_Rect& rect)
    : texture_id(texture_id)
    , clip(rect)
    {}

    TextureID texture_id;
    SDL_Rect clip;
};

#endif /* SPRITE_H_ */
