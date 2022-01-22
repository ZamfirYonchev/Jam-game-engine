/*
 * texture.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <string>
#include <iostream>
#include "font.h"

class Texture
{
public:
	Texture(std::string_view filename, SDL_Renderer& renderer)
	: m_texture{nullptr}
	{
		const std::unique_ptr<SDL_Surface, SDL_Surface_Destructor> surface { IMG_Load(filename.data()) };

        if(surface == nullptr)
        {
            std::cerr << "Cannot load image " << filename << "! Error: " << IMG_GetError() << std::endl;
        }
        else
        {
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
            m_texture.reset(SDL_CreateTextureFromSurface(&renderer, surface.get()));
            if(m_texture == nullptr)
            {
                std::cerr << "Cannot create texture from " << filename << "! Error: " << SDL_GetError() << std::endl;
            }
        }
	}

	Texture(std::string_view text, Font& font, uint8_t r, uint8_t g, uint8_t b, SDL_Renderer& renderer)
	: m_texture{nullptr}
	{
        SDL_Surface* surface = TTF_RenderText_Solid(font.font(), text.data(), SDL_Color{r, g, b, 0});

        if(surface == nullptr)
        {
            std::cerr << "Cannot render string '" << text << "'! Error: " << TTF_GetError() << std::endl;
        }
        else
        {
            m_texture.reset(SDL_CreateTextureFromSurface(&renderer, surface));
            if(m_texture == nullptr)
            {
                std::cerr << "Cannot create texture for string '" << text << "'! Error: " << SDL_GetError() << std::endl;
            }
            SDL_FreeSurface(surface);
        }
	}

    SDL_Texture* texture()
    {
        return m_texture.get();
    }

private:
    struct SDL_Texture_Destructor { void operator()(SDL_Texture* ptr) { SDL_DestroyTexture(ptr); } };
    struct SDL_Surface_Destructor { void operator()(SDL_Surface* ptr) { SDL_FreeSurface(ptr); } };

    std::unique_ptr<SDL_Texture, SDL_Texture_Destructor> m_texture;
};

#endif /* TEXTURE_H_ */
