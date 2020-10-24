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
#include <limits>
#include "math_ext.h"

SdlWindow::~SdlWindow()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

void SdlWindow::init_video(uint16_t& res_width
						  ,uint16_t& res_height
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

	const uint32_t requested_size = res_width * res_height;
	uint32_t closest_size_diff = std::numeric_limits<uint32_t>::max();
	uint16_t final_res_w = res_width, final_res_h = res_height;

    for(int display_mode_i = 0; display_mode_i < SDL_GetNumDisplayModes(0); ++display_mode_i)
    {
        SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
        if (SDL_GetDisplayMode(0, display_mode_i, &mode) != 0)
        {
            std::cerr << "SDL_GetDisplayMode failed: " << SDL_GetError() << std::endl;
            return;
        }

        const uint32_t size_diff = requested_size + mode.w*mode.h - 2*min(int(res_width), mode.w) * min(int(res_height), mode.h);
		if(size_diff < closest_size_diff)
		{
			closest_size_diff = size_diff;
			final_res_w = mode.w;
			final_res_h = mode.h;
		}
    }
    std::cout << "Chosen resolution is " << final_res_w << " by " << final_res_h << std::endl;

	uint32_t flags = SDL_WINDOW_OPENGL;

	if(fullscreen == true) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

	SDL_CreateWindowAndRenderer(final_res_w, final_res_h, flags, &m_window, &m_renderer);

	if(!m_window || !m_renderer)
	{
		std::cerr << "Unable to initialize video " << SDL_GetError() << std::endl;
		return;
	}

	res_width = final_res_w;
	res_height = final_res_h;

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
	SDL_SetWindowTitle(m_window, "Game");

	std::cout << "Video initialized" << std::endl;
}

