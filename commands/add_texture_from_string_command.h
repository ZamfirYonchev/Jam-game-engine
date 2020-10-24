/*
 * add_texture_from_string_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_TEXTURE_FROM_STRING_COMMAND_H_
#define COMMANDS_ADD_TEXTURE_FROM_STRING_COMMAND_H_

#include <string>
#include "../types.h"
#include "../systems/resource_system.h"
#include "../systems/rendering_system.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class AddTextureFromStringCommand
{
public:
    AddTextureFromStringCommand(const std::string& text, AbsFontID font_id, uint8_t r, uint8_t g, uint8_t b)
	: m_text(text)
	, m_font_id(font_id)
	, m_r(r)
	, m_g(g)
	, m_b(b)
	{}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
    {
    	resource_system.addNewTextureFromString(m_text, m_font_id, m_r, m_g, m_b, rendering_system.renderer());
    }

private:
    std::string m_text;
    AbsFontID m_font_id;
    uint8_t m_r, m_g, m_b;
};


#endif /* COMMANDS_ADD_TEXTURE_FROM_STRING_COMMAND_H_ */
