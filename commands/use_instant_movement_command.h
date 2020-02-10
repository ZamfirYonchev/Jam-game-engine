/*
 * use_instant_movement_command.h
 *
 *  Created on: Dec 8, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_INSTANT_MOVEMENT_COMMAND_H_
#define COMMANDS_USE_INSTANT_MOVEMENT_COMMAND_H_

#include "command.h"

class UseInstantMovementCommand : public Command
{
public:
	UseInstantMovementCommand(double move_accel)
	: m_move_accel(move_accel)
	{}

	void execute() const;
	std::unique_ptr<Command> clone() { return std::make_unique<UseInstantMovementCommand>(m_move_accel); }

private:
    double m_move_accel;
};

#endif /* COMMANDS_USE_INSTANT_MOVEMENT_COMMAND_H_ */
