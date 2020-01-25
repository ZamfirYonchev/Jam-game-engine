/*
 * use_static_visuals_command.h
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_STATIC_VISUALS_COMMAND_H_
#define COMMANDS_USE_STATIC_VISUALS_COMMAND_H_

#include "command.h"
#include "../types.h"

class UseStaticVisualsCommand : public Command
{
public:
	UseStaticVisualsCommand(SpritesheetID spr_id, int sprite)
	: m_spr_id(spr_id)
	, m_sprite(sprite)
	{}

    void execute() const;
    Command* clone() { return new UseStaticVisualsCommand(m_spr_id, m_sprite); }
private:
    SpritesheetID m_spr_id;
    int m_sprite;
};

#endif /* COMMANDS_USE_STATIC_VISUALS_COMMAND_H_ */
