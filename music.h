/*
 * music.h
 *
 *  Created on: Nov 12, 2020
 *      Author: zamfi
 */

#ifndef MUSIC_H_
#define MUSIC_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>
#include <memory>

class Music
{
public:
	Music(std::string_view filename)
	: m_music(Mix_LoadMUS(filename.data()))
	{
        if(m_music == nullptr)
        {
            std::cerr << "Cannot load music " << filename << "! Error: " << Mix_GetError() << std::endl;
        }
	}

    Mix_Music* music() const
    {
        return m_music.get();
    }

private:
    struct Mix_Music_Destructor { void operator()(Mix_Music* ptr) { Mix_FreeMusic(ptr); } };

    std::unique_ptr<Mix_Music, Mix_Music_Destructor> m_music;
};

#endif /* MUSIC_H_ */
