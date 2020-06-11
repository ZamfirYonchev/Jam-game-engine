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
	UseInstantMovementCommand(double mass, double friction, double move_force)
	: m_mass(mass)
	, m_friction(friction)
	, m_move_force(move_force)
	{}

    void execute() const;
	std::unique_ptr<Command> clone() { return std::make_unique<UseInstantMovementCommand>(m_mass, m_friction, m_move_force); }

private:
    double m_mass, m_friction, m_move_force;
};

#endif /* COMMANDS_USE_INSTANT_MOVEMENT_COMMAND_H_ */
