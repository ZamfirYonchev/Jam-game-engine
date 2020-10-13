/*
 * add_visual_object_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_VISUAL_OBJECT_COMMAND_H_
#define COMMANDS_ADD_VISUAL_OBJECT_COMMAND_H_

#include "command.h"
#include "../types.h"
#include "../components/absolute_position.h"

class AddVisualObjectCommand : public Command
{
public:
    AddVisualObjectCommand(const AbsolutePosition& pos, SpritesheetID spr_id, int sprite)
	: m_pos(pos)
	, m_spr_id(spr_id)
	, m_sprite(sprite)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<AddVisualObjectCommand>(m_pos, m_spr_id, m_sprite); }

private:
    AbsolutePosition m_pos;
    SpritesheetID m_spr_id;
    int m_sprite;
};



#endif /* COMMANDS_ADD_VISUAL_OBJECT_COMMAND_H_ */
