/*
 * sound_chunk.h
 *
 *  Created on: Nov 12, 2020
 *      Author: zamfi
 */

#ifndef SOUND_CHUNK_H_
#define SOUND_CHUNK_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>

class SoundChunk
{
public:
	SoundChunk(const std::string& file, const int repeat) : m_sound(nullptr), m_repeat(repeat)
	{
		load_from_wav_file(file);
	}

	SoundChunk(const std::string& file) : SoundChunk(file, 1) {}

	SoundChunk() : m_sound(nullptr), m_repeat(0) {}

    ~SoundChunk()
    {
        unload();
    }

    SoundChunk(const SoundChunk&) = delete;
    SoundChunk(SoundChunk&& rhs) noexcept
    : m_sound(std::move(rhs.m_sound))
    , m_repeat(std::move(rhs.m_repeat))
    {
    	rhs.m_sound = nullptr;
    }

    SoundChunk& operator=(const SoundChunk&) = delete;
    SoundChunk& operator=(SoundChunk&& rhs) noexcept
    {
    	unload();
    	m_sound = rhs.m_sound;
    	rhs.m_sound = nullptr;

    	return *this;
    }

    SoundChunk& load_from_wav_file(const std::string& file)
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

    int repeat() const
    {
    	return m_repeat;
    }

private:
    Mix_Chunk* m_sound;
    int m_repeat;
};

#endif /* SOUND_CHUNK_H_ */
