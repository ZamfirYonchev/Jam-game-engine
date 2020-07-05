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

class AddPlatformCommand : public Command
{
public:
    AddPlatformCommand(double x, double y, double w, double h, SpritesheetID spr_id, double tile_w, double tile_h)
	: m_x(x)
	, m_y(y)
	, m_w(w)
	, m_h(h)
	, m_spr_id(spr_id)
	, m_tile_w(tile_w)
	, m_tile_h(tile_h)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<AddPlatformCommand>(m_x, m_y, m_w, m_h, m_spr_id, m_tile_w, m_tile_h); }

private:
    double m_x, m_y, m_w, m_h;
    SpritesheetID m_spr_id;
    double m_tile_w, m_tile_h;
};


#endif /* COMMANDS_ADD_PLATFORM_COMMAND_H_ */
