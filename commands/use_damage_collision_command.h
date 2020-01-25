/*
 * use_damage_collision_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_DAMAGE_COLLISION_COMMAND_H_
#define COMMANDS_USE_DAMAGE_COLLISION_COMMAND_H_

#include "command.h"
#include "../components/collision.h"

class UseDamageCollisionCommand : public Command
{
public:
	UseDamageCollisionCommand(Collision::CollisionState state, double damage)
	: m_state(state)
	, m_damage(damage)
	{}

    void execute() const;
    Command* clone() { return new UseDamageCollisionCommand(m_state, m_damage); }
private:
    Collision::CollisionState m_state;
    double m_damage;
};



#endif /* COMMANDS_USE_DAMAGE_COLLISION_COMMAND_H_ */
