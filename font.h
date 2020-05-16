/*
 * font.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef FONT_H_
#define FONT_H_

#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class Font
{
public:
	Font(const std::string& font_file, int size) : m_font(nullptr)
	{
		set_font(font_file, size);
	}

	Font() : m_font(nullptr) {}

	~Font()
	{
		if(m_font != nullptr)
			TTF_CloseFont(m_font);
	}

	Font(const Font&) = delete;
	Font(Font&& rhs) : m_font(std::move(rhs.m_font)) { rhs.m_font = nullptr; }

	Font& operator=(const Font&) = delete;
	Font& operator=(Font&& rhs)
	{
		if(m_font != nullptr)
			TTF_CloseFont(m_font);

		m_font = rhs.m_font;
		rhs.m_font = nullptr;

		return *this;
	}

	void set_font(const std::string& font_file, int size)
	{
		if(m_font)
			TTF_CloseFont(m_font);

		m_font = TTF_OpenFont(font_file.c_str(), size);
	    if(m_font == nullptr)
	    {
	    	std::cerr << "Failed to load " << font_file << " font: " << TTF_GetError() << std::endl;
	    }
	}

	TTF_Font* font()
	{
		return m_font;
	}

private:
	TTF_Font *m_font;
};

#endif /* FONT_H_ */
