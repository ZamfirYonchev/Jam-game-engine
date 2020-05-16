/*
 * use_full_movement_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_FULL_MOVEMENT_COMMAND_H_
#define COMMANDS_USE_FULL_MOVEMENT_COMMAND_H_

#include "command.h"

class UseFullMovementCommand : public Command
{
public:
	UseFullMovementCommand(double max_vx, double max_vy, double move_accel, double jump_accel, bool gravity_affected)
	: m_max_vx(max_vx)
	, m_max_vy(max_vy)
	, m_move_accel(move_accel)
	, m_jump_accel(jump_accel)
	, m_gravity_affected(gravity_affected)
	{}

	void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseFullMovementCommand>(m_max_vx, m_max_vy, m_move_accel, m_jump_accel, m_gravity_affected); }

private:
    double m_max_vx, m_max_vy, m_move_accel, m_jump_accel;
	bool m_gravity_affected;
};


#endif /* COMMANDS_USE_FULL_MOVEMENT_COMMAND_H_ */
