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
	ModifyMovementCommand(double mass, double friction, double vx, double vy, double fx, double fy, double gravity_affected)
	: m_mass(mass)
	, m_friction(friction)
	, m_vx(vx)
	, m_vy(vy)
	, m_fx(fx)
	, m_fy(fy)
	, m_gravity_affected(gravity_affected)
	{}

	void execute() const;
	std::unique_ptr<Command> clone() { return std::make_unique<ModifyMovementCommand>(m_mass, m_friction, m_vx, m_vy, m_fx, m_fy, m_gravity_affected); }
private:
    double m_mass, m_friction, m_vx, m_vy, m_fx, m_fy, m_gravity_affected;
};


#endif /* COMMANDS_MODIFY_MOVEMENT_COMMAND_H_ */
