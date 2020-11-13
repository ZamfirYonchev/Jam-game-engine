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

class Music
{
public:
	Music(const std::string& filename) : m_music(nullptr)
	{
		load_from_file(filename);
	}

	Music() : m_music(nullptr) {}

    ~Music()
    {
        unload();
    }

    Music(const Music&) = delete;
    Music(Music&& rhs) noexcept : m_music(rhs.m_music)
    {
    	rhs.m_music = nullptr;
    }

    Music& operator=(const Music&) = delete;
    Music& operator=(Music&& rhs) noexcept
    {
    	unload();
    	m_music = rhs.m_music;
    	rhs.m_music = nullptr;

    	return *this;
    }

    Music& load_from_file(const std::string& file)
    {
        unload();
        m_music = Mix_LoadMUS(file.c_str());

        if(m_music == nullptr)
        {
            std::cerr << "Cannot load music " << file << "! Error: " << Mix_GetError() << std::endl;
        }

        return *this;
    }

    void unload() noexcept
    {
        if(m_music != nullptr)
        {
        	Mix_FreeMusic(m_music);
        	m_music = nullptr;
        }
    }

    Mix_Music* music() const
    {
        return m_music;
    }

private:
    Mix_Music* m_music;
};

#endif /* MUSIC_H_ */
