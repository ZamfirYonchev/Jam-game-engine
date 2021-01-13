/*
 * resource_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_RESOURCE_SYSTEM_H_
#define SYSTEMS_RESOURCE_SYSTEM_H_

#include <vector>
#include "../types.h"
#include "../texture.h"
#include "../font.h"
#include "../spritesheet.h"
#include "../music.h"
#include "../sound_chunk.h"

class ResourceSystem
{
public:
    ResourceSystem() = default;

    TextureID addNewTextureFromFile(std::string_view file, SDL_Renderer* renderer)
    {
        m_textures.emplace_back();
        m_textures.back().load_from_file(file, renderer);
        return m_textures.size()-1;
    }

    TextureID addNewTextureFromString
	(
		std::string_view text
	  , const FontID font_id
	  , const uint8_t r
	  , const uint8_t g
	  , const uint8_t b
	  , SDL_Renderer* renderer
	)
    {
    	if(0 <= font_id && font_id < static_cast<FontID>(m_fonts.size()))
    	{
    		m_textures.emplace_back();
    		m_textures.back().load_from_string(text, m_fonts[font_id], r, g, b, renderer);
            return m_textures.size()-1;
    	}
    	else
    	{
    		//error font_id
    		return -1;
    	}
    }

    SpritesheetID addNewSpritesheet(const Spritesheet& spritesheet)
    {
    	const SpritesheetID spr_id = m_spritesheets.size();
        m_spritesheets.push_back(spritesheet);
        return spr_id;
    }

    void addNewSprite(const SpritesheetID spritesheet_id, const Sprite& sprite)
    {
    	if(0 <= spritesheet_id && spritesheet_id < static_cast<SpritesheetID>(m_spritesheets.size())
    	&& 0 <= sprite.texture_id && sprite.texture_id < static_cast<TextureID>(m_textures.size()))
        {
        	m_spritesheets[spritesheet_id].add_sprite(sprite.texture_id, sprite.clip.x, sprite.clip.y, sprite.clip.w, sprite.clip.h);
        }
        else
        {
        	// error spritesheet_id
        }
    }

    FontID addNewFont(std::string_view font_file, const int size)
    {
    	const FontID font_id = m_fonts.size();
    	m_fonts.push_back(Font(font_file, size));
    	return font_id;
    }

    SoundID addNewSound(std::string_view sound_file, const int repeat)
    {
    	const SoundID sound_id = m_sounds.size();
    	m_sounds.push_back(SoundChunk(sound_file, repeat));
    	return sound_id;
    }

    MusicID addNewMusic(std::string_view file)
    {
    	const MusicID music_id = m_music.size();
    	m_music.push_back(Music(file));
    	return music_id;
    }

    optional_ref<Texture> texture(const TextureID tex_id)
    {
        if(0 <= tex_id && tex_id < static_cast<TextureID>(m_textures.size()))
            return optional_ref<Texture>(m_textures[tex_id]);
        else
        	return optional_ref<Texture>();
    }

    const std::vector<Spritesheet>& spritesheets() const
    {
        return m_spritesheets;
    }

    optional_ref<Spritesheet> spritesheet(const SpritesheetID spr_id)
    {
        if(0 <= spr_id && spr_id < static_cast<SpritesheetID>(m_spritesheets.size()))
        	return optional_ref<Spritesheet>(m_spritesheets[spr_id]);
        else
        	return optional_ref<Spritesheet>();
    }

    optional_ref<Font> font(const FontID id)
    {
    	if(0 <= id && id < static_cast<FontID>(m_fonts.size()))
    		return optional_ref<Font>(m_fonts[id]);
    	else
    		return optional_ref<Font>();
    }

    optional_ref<SoundChunk> sound(const SoundID id)
    {
    	if(0 <= id && id < static_cast<SoundID>(m_sounds.size()))
    		return optional_ref<SoundChunk>(m_sounds[id]);
    	else
    		return optional_ref<SoundChunk>();
    }

    optional_ref<Music> music(const MusicID id)
    {
    	if(0 <= id && id < static_cast<MusicID>(m_music.size()))
    		return optional_ref<Music>(m_music[id]);
    	else
    		return optional_ref<Music>();
    }

    void clear_textures()
    {
        m_textures.clear();
    }

    void clear_spritesheets()
    {
        m_spritesheets.clear();
    }

    void clear_fonts()
    {
        m_fonts.clear();
    }

    void clear_sounds()
    {
        m_sounds.clear();
        m_music.clear();
    }

    void clear()
    {
        clear_textures();
        clear_spritesheets();
        clear_fonts();
        clear_sounds();
    }

private:
    std::vector<Texture> m_textures;
    std::vector<Spritesheet> m_spritesheets;
    std::vector<Font> m_fonts;
    std::vector<SoundChunk> m_sounds;
    std::vector<Music> m_music;
};

#endif /* SYSTEMS_RESOURCE_SYSTEM_H_ */
