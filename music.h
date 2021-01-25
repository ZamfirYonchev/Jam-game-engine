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
	Music(std::string_view filename) : m_music(nullptr)
	{
		load_from_file(filename);
	}

	Music() : m_music(nullptr) {}

    Music& load_from_file(std::string_view file)
    {
        m_music.reset(Mix_LoadMUS(file.data()));

        if(m_music == nullptr)
        {
            std::cerr << "Cannot load music " << file << "! Error: " << Mix_GetError() << std::endl;
        }

        return *this;
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
