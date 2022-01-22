/*
 * sdl_window.h
 *
 *  Created on: Nov 7, 2019
 *      Author: zamfi
 */

#ifndef SDL_WINDOW_H_
#define SDL_WINDOW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class SdlWindow
{
public:
	SdlWindow(const int res_width
			  , const int res_height
			  , const bool fullscreen
			  , const bool enable_audio
			  , const int sound_channels
			  , std::string_view title
			  , bool& success
		);

	~SdlWindow()
	{
		SDL_DestroyWindow(m_window);
		SDL_DestroyRenderer(m_renderer);
		if(m_audio_init) Mix_CloseAudio();
		if(m_img_init) IMG_Quit();
		if(m_ttf_init) TTF_Quit();
		if(m_audio_init) Mix_Quit();
		if(m_sdl_init) SDL_Quit();
	}

	SdlWindow(const SdlWindow&) = delete;
	SdlWindow(SdlWindow&& rhs) noexcept
		: m_window{rhs.m_window}
		, m_renderer{rhs.m_renderer}
		, m_sdl_init{rhs.m_sdl_init}
		, m_img_init{rhs.m_img_init}
		, m_ttf_init{rhs.m_ttf_init}
		, m_audio_init{rhs.m_audio_init}
		, m_res_w{rhs.m_res_w}
		, m_res_h{rhs.m_res_h}
	{
		rhs.m_window = nullptr;
		rhs.m_renderer = nullptr;
		rhs.m_sdl_init = false;
		rhs.m_img_init = false;
		rhs.m_ttf_init = false;
		rhs.m_audio_init = false;
	}

	SdlWindow& operator=(const SdlWindow&) = delete;
	SdlWindow& operator=(SdlWindow&& rhs) noexcept
	{
		SDL_DestroyWindow(m_window);
		SDL_DestroyRenderer(m_renderer);

		m_window = rhs.m_window;
		m_renderer = rhs.m_renderer;
		m_sdl_init = rhs.m_sdl_init;
		m_img_init = rhs.m_img_init;
		m_ttf_init = rhs.m_ttf_init;
		m_audio_init = rhs.m_audio_init;

		rhs.m_window = nullptr;
		rhs.m_renderer = nullptr;
		rhs.m_sdl_init = false;
		rhs.m_img_init = false;
		rhs.m_ttf_init = false;
		rhs.m_audio_init = false;

		return *this;
	}

	SDL_Renderer& renderer() { return *m_renderer; }
	int res_width() const { return m_res_w; }
	int res_height() const { return m_res_h; }

private:
	//TODO use unique_ptr instead of raw pointers
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	bool m_sdl_init;
	bool m_img_init;
	bool m_ttf_init;
	bool m_audio_init;
	int m_res_w;
	int m_res_h;
};



#endif /* SDL_WINDOW_H_ */
