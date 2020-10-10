/*
 * add_texture_from_string_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_TEXTURE_FROM_STRING_COMMAND_H_
#define COMMANDS_ADD_TEXTURE_FROM_STRING_COMMAND_H_

#include "command.h"
#include <string>
#include <SDL2/SDL.h>
#include "../types.h"

class AddTextureFromStringCommand : public Command
{
public:
    AddTextureFromStringCommand(const std::string& text, FontID font_id, uint8_t r, uint8_t g, uint8_t b, SDL_Renderer* renderer)
	: m_text(text)
	, m_font_id(font_id)
	, m_r(r)
	, m_g(g)
	, m_b(b)
	, m_renderer(renderer) {}

    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<AddTextureFromStringCommand>(m_text, m_font_id, m_r, m_g, m_b, m_renderer); }

private:
    std::string m_text;
    FontID m_font_id;
    uint8_t m_r, m_g, m_b;
    SDL_Renderer* m_renderer;
};


#endif /* COMMANDS_ADD_TEXTURE_FROM_STRING_COMMAND_H_ */
