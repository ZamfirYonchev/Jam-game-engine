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
    AddPlatformCommand(double x, double y, double w, double h, SpritesheetID spr_id, double rx, double ry)
	: m_x(x)
	, m_y(y)
	, m_w(w)
	, m_h(h)
	, m_spr_id(spr_id)
	, m_rx(rx)
	, m_ry(ry)
	{}

    void execute() const;
    Command* clone() { return new AddPlatformCommand(m_x, m_y, m_w, m_h, m_spr_id, m_rx, m_ry); }

private:
    double m_x, m_y, m_w, m_h;
    SpritesheetID m_spr_id;
    double m_rx, m_ry;
};


#endif /* COMMANDS_ADD_PLATFORM_COMMAND_H_ */
