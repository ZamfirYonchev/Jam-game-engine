/*
 * sdl_window.h
 *
 *  Created on: Nov 7, 2019
 *      Author: zamfi
 */

#ifndef SDL_WINDOW_H_
#define SDL_WINDOW_H_

#include <SDL2/SDL.h>

class SdlWindow
{
public:
	SdlWindow() : m_window(nullptr), m_renderer(nullptr)
	{}

	void init_video(const uint16_t res_width
				  , const uint16_t res_height
				  , const bool fullscreen
				  , const bool double_buffer
			);

	~SdlWindow();

	SdlWindow(const SdlWindow&) = delete;
	SdlWindow(SdlWindow&& rhs) : m_window(rhs.m_window), m_renderer(rhs.m_renderer)
	{
		rhs.m_window = nullptr;
		rhs.m_renderer = nullptr;
	}

	SdlWindow& operator=(const SdlWindow&) = delete;
	SdlWindow& operator=(SdlWindow&& rhs)
	{
		SDL_DestroyWindow(m_window);
		SDL_DestroyRenderer(m_renderer);

		m_window = rhs.m_window;
		m_renderer = rhs.m_renderer;

		rhs.m_window = nullptr;
		rhs.m_renderer = nullptr;

		return *this;
	}

	SDL_Renderer* renderer()
	{
		return m_renderer;
	}

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};



#endif /* SDL_WINDOW_H_ */
