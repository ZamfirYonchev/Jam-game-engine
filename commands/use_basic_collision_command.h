/*
 * use_basic_collision_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_BASIC_COLLISION_COMMAND_H_
#define COMMANDS_USE_BASIC_COLLISION_COMMAND_H_

#include "command.h"
#include "../components/collision.h"

class UseBasicCollisionCommand : public Command
{
public:
	UseBasicCollisionCommand(Collision::CollisionState state)
	: m_state(state)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseBasicCollisionCommand>(m_state); }
private:
    Collision::CollisionState m_state;
};


#endif /* COMMANDS_USE_BASIC_COLLISION_COMMAND_H_ */
