/*
 * use_tiled_visuals_command.h
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_TILED_VISUALS_COMMAND_H_
#define COMMANDS_USE_TILED_VISUALS_COMMAND_H_

#include "command.h"
#include "../types.h"

class UseTiledVisualsCommand : public Command
{
public:
	UseTiledVisualsCommand(SpritesheetID spr_id, uint16_t repeat_x, uint16_t repeat_y)
	: m_spr_id(spr_id)
	, m_repeat_x(repeat_x)
	, m_repeat_y(repeat_y)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseTiledVisualsCommand>(m_spr_id, m_repeat_x, m_repeat_y); }
private:
    SpritesheetID m_spr_id;
    uint16_t m_repeat_x, m_repeat_y;
};

#endif /* COMMANDS_USE_TILED_VISUALS_COMMAND_H_ */
