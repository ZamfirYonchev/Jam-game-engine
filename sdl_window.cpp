/*
 * sdl_window.cpp
 *
 *  Created on: Nov 7, 2019
 *      Author: zamfi
 */

#include "sdl_window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>


SdlWindow::~SdlWindow()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);

	SDL_Quit();
}

void SdlWindow::init_video(const uint16_t res_width
						  , const uint16_t res_height
						  , const uint16_t bits_per_pixel
						  , const bool fullscreen
						  , const bool double_buffer
					)
{
	if(m_window)
	{
		SDL_DestroyWindow(m_window);
		SDL_DestroyRenderer(m_renderer);
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();

		m_window = nullptr;
		m_renderer = nullptr;
	}

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Unable to init SDL " << SDL_GetError() << std::endl;
		return;
	}

    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cerr << "Unable to initialize SDL_image" << IMG_GetError() << std::endl;
        return;
    }

    if(TTF_Init() < 0)
    {
        std::cerr << "Unable to initialize SDL_ttf" << TTF_GetError() << std::endl;
        return;
    }

	atexit(SDL_Quit);

	uint32_t flags = SDL_WINDOW_OPENGL;

	if(fullscreen == true) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

	SDL_CreateWindowAndRenderer(res_width, res_height, flags, &m_window, &m_renderer);

	if(!m_window || !m_renderer)
	{
		std::cerr << "Unable to initialize video " << SDL_GetError() << std::endl;
		return;
	}

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
	SDL_SetWindowTitle(m_window, "Game");

	std::cout << "Video initialized" << std::endl;
}

