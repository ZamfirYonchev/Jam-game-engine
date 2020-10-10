/*
 * add_projectile_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_PROJECTILE_COMMAND_H_
#define COMMANDS_ADD_PROJECTILE_COMMAND_H_

#include "command.h"
#include "../types.h"

class AddProjectileCommand : public Command
{
public:
    AddProjectileCommand(double x, double y, double w, double h, SpritesheetID spr_id)
	: m_x(x)
	, m_y(y)
	, m_w(w)
	, m_h(h)
	, m_spr_id(spr_id)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<AddProjectileCommand>(m_x, m_y, m_w, m_h, m_spr_id); }

private:
    double m_x, m_y, m_w, m_h;
    SpritesheetID m_spr_id;
};



#endif /* COMMANDS_ADD_PROJECTILE_COMMAND_H_ */
