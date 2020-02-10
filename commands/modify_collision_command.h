/*
 * modify_collision_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_COLLISION_COMMAND_H_
#define COMMANDS_MODIFY_COLLISION_COMMAND_H_

#include "command.h"

class ModifyCollisionCommand : public Command
{
public:
	ModifyCollisionCommand(double state, double standing_on, double on_collision_damage)
	: m_state(state)
	, m_standing_on(standing_on)
	, m_on_collision_damage(on_collision_damage)
	{}

	void execute() const;
	std::unique_ptr<Command> clone() { return std::make_unique<ModifyCollisionCommand>(m_state, m_standing_on, m_on_collision_damage); }
private:
	double m_state, m_standing_on, m_on_collision_damage;
};

#endif /* COMMANDS_MODIFY_COLLISION_COMMAND_H_ */
