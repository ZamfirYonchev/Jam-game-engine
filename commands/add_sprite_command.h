/*
 * add_sprite_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_SPRITE_COMMAND_H_
#define COMMANDS_ADD_SPRITE_COMMAND_H_

#include "command.h"
#include "../types.h"

class AddSpriteCommand : public Command
{
public:
    AddSpriteCommand(SpritesheetID spr_id, TextureID tex_id, int x, int y, int w, int h)
    : m_spr_id(spr_id)
    , m_tex_id(tex_id)
    , m_x(x)
    , m_y(y)
    , m_w(w)
    , m_h(h)
    {}
    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<AddSpriteCommand>(m_spr_id, m_tex_id, m_x, m_y, m_w, m_h); }

private:
    SpritesheetID m_spr_id;
    TextureID m_tex_id;
    int m_x, m_y, m_w, m_h;
};


#endif /* COMMANDS_ADD_SPRITE_COMMAND_H_ */
