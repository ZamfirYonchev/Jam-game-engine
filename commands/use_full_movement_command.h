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
	UseFullMovementCommand(double mass, double friction, double move_force, double jump_force, bool gravity_affected)
	: m_mass(mass)
	, m_friction(friction)
	, m_move_force(move_force)
	, m_jump_force(jump_force)
	, m_gravity_affected(gravity_affected)
	{}

	void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseFullMovementCommand>(m_mass, m_friction, m_move_force, m_jump_force, m_gravity_affected); }

private:
    double m_mass, m_friction, m_move_force, m_jump_force;
	bool m_gravity_affected;
};


#endif /* COMMANDS_USE_FULL_MOVEMENT_COMMAND_H_ */
