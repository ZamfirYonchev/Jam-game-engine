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

class AddVisualObjectCommand : public Command
{
public:
    AddVisualObjectCommand(double x, double y, double w, double h, SpritesheetID spr_id, int sprite)
	: m_x(x)
	, m_y(y)
	, m_w(w)
	, m_h(h)
	, m_spr_id(spr_id)
	, m_sprite(sprite)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<AddVisualObjectCommand>(m_x, m_y, m_w, m_h, m_spr_id, m_sprite); }

private:
    double m_x, m_y, m_w, m_h;
    SpritesheetID m_spr_id;
    int m_sprite;
};



#endif /* COMMANDS_ADD_VISUAL_OBJECT_COMMAND_H_ */
