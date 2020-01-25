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

class ResourceSystem
{
public:
    ResourceSystem() {}

    ~ResourceSystem()
    {
        clear();
    }

    ResourceSystem(const ResourceSystem&) = delete;
    ResourceSystem(ResourceSystem&& rhs) : m_fonts(std::move(rhs.m_fonts))
    									 , m_procedures(std::move(rhs.m_procedures))
    									 , m_spritesheets(std::move(rhs.m_spritesheets))
    									 , m_textures(std::move(rhs.m_textures))
    {}

    ResourceSystem& operator=(const ResourceSystem&) = delete;
    ResourceSystem& operator=(ResourceSystem&& rhs)
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
        return m_textures.size()-1;
    }

    SpritesheetID last_spritesheet_id() const
    {
        return m_spritesheets.size()-1;
    }

    ProcedureID last_procedure_id() const
    {
        return m_procedures.size()-1;
    }

    FontID last_font_id() const
    {
    	return m_fonts.size()-1;
    }

    void addNewTextureFromFile(const std::string& file, SDL_Renderer* renderer)
    {
    	Texture* texture = new Texture();
    	texture->load_from_file(file, renderer);
        m_textures.push_back(texture);
    }

    void addNewTextureFromString(const std::string& text, FontID font_id, uint8_t r, uint8_t g, uint8_t b, SDL_Renderer* renderer)
    {
    	assert(font_id < m_fonts.size());
    	Texture* texture = new Texture();
    	texture->load_from_string(text, m_fonts[font_id], r, g, b, renderer);
        m_textures.push_back(texture);
    }

    void addNewSpritesheet(int idle_start, int idle_size
                         , int walk_start, int walk_size
                         , int jump_start, int jump_size
                         , int fall_start, int fall_size
                         , int attack_start, int attack_size
                         , int hit_start, int hit_size
                         , int dead_start, int dead_size
                         , double scale_factor
                          )
    {
        m_spritesheets.push_back(new Spritesheet(idle_start, idle_size
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
        assert(spritesheet_id < m_spritesheets.size());
        m_spritesheets[spritesheet_id]->add_sprite(sprite.texture_id, sprite.clip.x, sprite.clip.y, sprite.clip.w, sprite.clip.h);
    }

    void addNewProcedure()
    {
        m_procedures.push_back(new ProcedureCommand());
    }

    void addNewFont(const std::string& font_file, int size)
    {
    	m_fonts.push_back(new Font(font_file, size));
    }

    const std::vector<Texture*>& textures() const
    {
        return m_textures;
    }

    Texture* texture(TextureID tex_id)
    {
        assert(tex_id < m_textures.size());
        return m_textures[tex_id];
    }

    const std::vector<Spritesheet*>& spritesheets() const
    {
        return m_spritesheets;
    }

    Spritesheet* spritesheet(SpritesheetID spr_id)
    {
        assert(spr_id < m_spritesheets.size());
        return m_spritesheets[spr_id];
    }

    const std::vector<ProcedureCommand*>& procedures() const
    {
        return m_procedures;
    }

    ProcedureCommand* procedure(ProcedureID id)
    {
        assert(id < m_procedures.size());
        return m_procedures[id];
    }

    Font* font(FontID id)
    {
    	assert(id < m_fonts.size());
    	return m_fonts[id];
    }

    void clear_textures()
    {
        for(auto it = m_textures.begin(); it != m_textures.end(); ++it)
            delete *it;

        m_textures.clear();
    }

    void clear_spritesheets()
    {
        for(auto it = m_spritesheets.begin(); it != m_spritesheets.end(); ++it)
            delete *it;

        m_spritesheets.clear();
    }

    void clear_procedures()
    {
        for(auto it = m_procedures.begin(); it != m_procedures.end(); ++it)
            delete *it;

        m_procedures.clear();
    }

    void clear_fonts()
    {
        for(auto it = m_fonts.begin(); it != m_fonts.end(); ++it)
            delete *it;

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
    std::vector<Texture*> m_textures;
    std::vector<Spritesheet*> m_spritesheets;
    std::vector<ProcedureCommand*> m_procedures;
    std::vector<Font*> m_fonts;
};





#endif /* SYSTEMS_RESOURCE_SYSTEM_H_ */
