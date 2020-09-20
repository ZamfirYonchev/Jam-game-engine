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
#include "../commands/procedure_command.h"
#include "../optional_ref.h"

class ResourceSystem
{
public:
    ResourceSystem() {}

    ~ResourceSystem()
    {
        clear();
    }

    ResourceSystem(const ResourceSystem&) = delete;
    ResourceSystem(ResourceSystem&& rhs) noexcept = default;

    ResourceSystem& operator=(const ResourceSystem&) = delete;
    ResourceSystem& operator=(ResourceSystem&& rhs) noexcept
    {
    	clear();
    	m_fonts = std::move(rhs.m_fonts);
    	m_procedures = std::move(rhs.m_procedures);
    	m_spritesheets = std::move(rhs.m_spritesheets);
    	m_textures = std::move(rhs.m_textures);

    	return *this;
    }

    TextureID last_texture_id() const
    {
        return TextureID(m_textures.size()-1);
    }

    SpritesheetID last_spritesheet_id() const
    {
        return SpritesheetID(m_spritesheets.size()-1);
    }

    ProcedureID last_procedure_id() const
    {
        return ProcedureID(m_procedures.size()-1);
    }

    FontID last_font_id() const
    {
    	return FontID(m_fonts.size()-1);
    }

    void addNewTextureFromFile(const std::string& file, SDL_Renderer* renderer)
    {
        m_textures.emplace_back();
        m_textures.back().load_from_file(file, renderer);
    }

    void addNewTextureFromString
	(
		const std::string& text
	  , const FontID font_id
	  , const uint8_t r
	  , const uint8_t g
	  , const uint8_t b
	  , SDL_Renderer* renderer
	)
    {
    	if(font_id < m_fonts.size())
    	{
    		m_textures.emplace_back();
    		m_textures.back().load_from_string(text, m_fonts[font_id], r, g, b, renderer);
    	}
    	else
    	{
    		//error font_id
    	}
    }

    void addNewSpritesheet(const int idle_start,   const int idle_size
                         , const int walk_start,   const int walk_size
                         , const int jump_start,   const int jump_size
                         , const int fall_start,   const int fall_size
                         , const int attack_start, const int attack_size
                         , const int hit_start,    const int hit_size
                         , const int dead_start,   const int dead_size
                         , const double scale_factor
                          )
    {
        m_spritesheets.push_back(Spritesheet(idle_start, idle_size
											   , walk_start, walk_size
											   , jump_start, jump_size
											   , fall_start, fall_size
											   , attack_start, attack_size
											   , hit_start, hit_size
											   , dead_start, dead_size
											   , scale_factor
												)
                                );
    }

    void addNewSprite(SpritesheetID spritesheet_id, const Sprite& sprite)
    {
        if(spritesheet_id < m_spritesheets.size())
        {
        	m_spritesheets[spritesheet_id].add_sprite(sprite.texture_id, sprite.clip.x, sprite.clip.y, sprite.clip.w, sprite.clip.h);
        }
        else
        {
        	// error spritesheet_id
        }
    }

    void addNewProcedure()
    {
        m_procedures.emplace_back();
    }

    void addNewFont(const std::string& font_file, int size)
    {
    	m_fonts.push_back(Font(font_file, size));
    }

    const std::vector<Texture>& textures() const
    {
        return m_textures;
    }

    optional_ref<Texture> texture(TextureID tex_id)
    {
        if(tex_id < m_textures.size())
            return optional_ref<Texture>(m_textures[tex_id]);
        else
        	return optional_ref<Texture>();
    }

    const std::vector<Spritesheet>& spritesheets() const
    {
        return m_spritesheets;
    }

    optional_ref<Spritesheet> spritesheet(SpritesheetID spr_id)
    {
        if(spr_id < m_spritesheets.size())
        	return optional_ref<Spritesheet>(m_spritesheets[spr_id]);
        else
        	return optional_ref<Spritesheet>();
    }

    const std::vector<ProcedureCommand>& procedures() const
    {
        return m_procedures;
    }

    optional_ref<ProcedureCommand> procedure(ProcedureID id)
    {
        if(id < m_procedures.size())
        	return optional_ref<ProcedureCommand>(m_procedures[id]);
		else
			return optional_ref<ProcedureCommand>();
    }

    optional_ref<Font> font(FontID id)
    {
    	if(id < m_fonts.size())
    		return optional_ref<Font>(m_fonts[id]);
    	else
    		return optional_ref<Font>();
    }

    void clear_textures()
    {
        m_textures.clear();
    }

    void clear_spritesheets()
    {
        m_spritesheets.clear();
    }

    void clear_procedures()
    {
        m_procedures.clear();
    }

    void clear_fonts()
    {
        m_fonts.clear();
    }

    void clear()
    {
        clear_textures();
        clear_spritesheets();
        clear_procedures();
        clear_fonts();
    }

private:
    std::vector<Texture> m_textures;
    std::vector<Spritesheet> m_spritesheets;
    std::vector<ProcedureCommand> m_procedures;
    std::vector<Font> m_fonts;
};





#endif /* SYSTEMS_RESOURCE_SYSTEM_H_ */
