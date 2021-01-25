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
#include <memory>

class SoundChunk
{
public:
	SoundChunk(std::string_view file, const int repeat) : m_sound(nullptr), m_repeat(repeat)
	{
		load_from_wav_file(file);
	}

	SoundChunk(std::string_view file) : SoundChunk(file, 1) {}

	SoundChunk() : m_sound(nullptr), m_repeat(0) {}

    SoundChunk& load_from_wav_file(std::string_view file)
    {
        m_sound.reset(Mix_LoadWAV(file.data()));

        if(m_sound == nullptr)
        {
            std::cerr << "Cannot load sound " << file << "! Error: " << Mix_GetError() << std::endl;
        }

        return *this;
    }

    Mix_Chunk* sound() const
    {
        return m_sound.get();
    }

    int repeat() const
    {
    	return m_repeat;
    }

private:
    struct Mix_Chunk_Destructor { void operator()(Mix_Chunk* ptr) { Mix_FreeChunk(ptr); } };

    std::unique_ptr<Mix_Chunk, Mix_Chunk_Destructor> m_sound;
    int m_repeat;
};

#endif /* SOUND_CHUNK_H_ */
