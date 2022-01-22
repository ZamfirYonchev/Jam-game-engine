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
#include <memory>

class Font
{
public:
	Font(std::string_view font_file, int size)
	: m_font{TTF_OpenFont(font_file.data(), size)}
	{
	    if(m_font == nullptr)
	    {
	    	std::cerr << "Failed to load " << font_file << " font: " << TTF_GetError() << std::endl;
	    }
	}

	TTF_Font* font()
	{
		return m_font.get();
	}

private:
    struct TTF_Font_Destructor { void operator()(TTF_Font* ptr) { TTF_CloseFont(ptr); } };

    std::unique_ptr<TTF_Font, TTF_Font_Destructor> m_font;
};

#endif /* FONT_H_ */
