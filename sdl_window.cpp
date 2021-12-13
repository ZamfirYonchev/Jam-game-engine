/*
 * sdl_window.cpp
 *
 *  Created on: Nov 7, 2019
 *      Author: zamfi
 */

#include "sdl_window.h"
#include <iostream>
#include <limits>
#include "math_ext.h"

SdlWindow::SdlWindow(
		const int res_width
	  , const int res_height
	  , const bool fullscreen
	  , const bool enable_audio
	  , const int sound_channels
	  , std::string_view title
	  , bool& success
	  )
	: m_window{nullptr}
	, m_renderer{nullptr}
	, m_sdl_init{false}
	, m_img_init{false}
	, m_ttf_init{false}
	, m_audio_init{false}
	, m_res_w{0}
	, m_res_h{0}
{
	const uint32_t sdl_init_flags = SDL_INIT_VIDEO | (enable_audio ? SDL_INIT_AUDIO : 0u);

	if(SDL_Init(sdl_init_flags) < 0)
	{
		std::cerr << "Unable to init SDL " << SDL_GetError() << std::endl;
		success = false;
		return;
	}
	m_sdl_init = true;

    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cerr << "Unable to initialize SDL_image" << IMG_GetError() << std::endl;
		success = false;
        return;
    }
    m_img_init = true;

    if(TTF_Init() < 0)
    {
        std::cerr << "Unable to initialize SDL_ttf" << TTF_GetError() << std::endl;
		success = false;
        return;
    }
    m_ttf_init = true;

    if(enable_audio)
    {
		if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_F32SYS, sound_channels, 2048) < 0)
		{
			std::cerr << "Unable to initialize SDL_mixer" << Mix_GetError() << std::endl;
			success = false;
			return;
		}
		m_audio_init = true;
    }

	atexit(SDL_Quit);

	const int requested_size = res_width * res_height;
	int closest_size_diff = std::numeric_limits<int>::max();
	int final_res_w = res_width, final_res_h = res_height;

    for(int display_mode_i = 0; display_mode_i < SDL_GetNumDisplayModes(0); ++display_mode_i)
    {
        SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
        if (SDL_GetDisplayMode(0, display_mode_i, &mode) != 0)
        {
            std::cerr << "SDL_GetDisplayMode failed: " << SDL_GetError() << std::endl;
    		success = false;
            return;
        }

        const int size_diff = requested_size + mode.w*mode.h - 2*min(res_width, mode.w) * min(res_height, mode.h);
		if(size_diff < closest_size_diff)
		{
			closest_size_diff = size_diff;
			final_res_w = mode.w;
			final_res_h = mode.h;
		}
    }

    m_res_w = final_res_w;
    m_res_h = final_res_h;

    std::cout << "Chosen resolution is " << m_res_w << " by " << m_res_h << std::endl;

	uint32_t flags = SDL_WINDOW_OPENGL;

	if(fullscreen == true) flags |= SDL_WINDOW_FULLSCREEN;

	SDL_CreateWindowAndRenderer(m_res_w, m_res_h, flags, &m_window, &m_renderer);

	if(!m_window || !m_renderer)
	{
		std::cerr << "Unable to initialize video " << SDL_GetError() << std::endl;
		success = false;
		return;
	}

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
	SDL_SetWindowTitle(m_window, title.data());

	std::cout << "Video initialized" << std::endl;
	success = true;
}

