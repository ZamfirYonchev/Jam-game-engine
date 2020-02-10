/*
 * modify_movement_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_MOVEMENT_COMMAND_H_
#define COMMANDS_MODIFY_MOVEMENT_COMMAND_H_

#include "command.h"

class ModifyMovementCommand : public Command
{
public:
	ModifyMovementCommand(double vx, double vy, double ax, double ay, double gravity_affected)
	: m_vx(vx)
	, m_vy(vy)
	, m_ax(ax)
	, m_ay(ay)
	, m_gravity_affected(gravity_affected)
	{}

	void execute() const;
	std::unique_ptr<Command> clone() { return std::make_unique<ModifyMovementCommand>(m_vx, m_vy, m_ax, m_ay, m_gravity_affected); }
private:
    double m_vx, m_vy, m_ax, m_ay, m_gravity_affected;
};


#endif /* COMMANDS_MODIFY_MOVEMENT_COMMAND_H_ */
