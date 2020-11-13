/*
 * sound.h
 *
 *  Created on: Nov 12, 2020
 *      Author: zamfi
 */

#ifndef SOUND_H_
#define SOUND_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>

class Sound
{
public:
	Sound(const std::string& file) : m_sound(nullptr)
	{
		load_from_wav_file(file);
	}

	Sound() : m_sound(nullptr) {}

    ~Sound()
    {
        unload();
    }

    Sound(const Sound&) = delete;
    Sound(Sound&& rhs) noexcept : m_sound(rhs.m_sound)
    {
    	rhs.m_sound = nullptr;
    }

    Sound& operator=(const Sound&) = delete;
    Sound& operator=(Sound&& rhs) noexcept
    {
    	unload();
    	m_sound = rhs.m_sound;
    	rhs.m_sound = nullptr;

    	return *this;
    }

    Sound& load_from_wav_file(const std::string& file)
    {
        unload();
        m_sound = Mix_LoadWAV(file.c_str());

        if(m_sound == nullptr)
        {
            std::cerr << "Cannot load sound " << file << "! Error: " << Mix_GetError() << std::endl;
        }

        return *this;
    }

    void unload() noexcept
    {
        if(m_sound != nullptr)
        {
        	Mix_FreeChunk(m_sound);
        	m_sound = nullptr;
        }
    }

    Mix_Chunk* sound() const
    {
        return m_sound;
    }

private:
    Mix_Chunk* m_sound;
};

#endif /* SOUND_H_ */
