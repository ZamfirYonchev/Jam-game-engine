/*
 * add_platform_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_PLATFORM_COMMAND_H_
#define COMMANDS_ADD_PLATFORM_COMMAND_H_

#include "command.h"
#include "../types.h"
#include "../components/absolute_position.h"

class AddPlatformCommand : public Command
{
public:
    AddPlatformCommand(const AbsolutePosition& pos, SpritesheetID spr_id, double tile_w, double tile_h)
	: m_pos(pos)
	, m_spr_id(spr_id)
	, m_tile_w(tile_w)
	, m_tile_h(tile_h)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<AddPlatformCommand>(m_pos, m_spr_id, m_tile_w, m_tile_h); }

private:
    AbsolutePosition m_pos;
    SpritesheetID m_spr_id;
    double m_tile_w, m_tile_h;
};


#endif /* COMMANDS_ADD_PLATFORM_COMMAND_H_ */
