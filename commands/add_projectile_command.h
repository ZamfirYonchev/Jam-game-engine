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
#include "../components/absolute_position.h"

class AddProjectileCommand : public Command
{
public:
    AddProjectileCommand(const AbsolutePosition& pos, SpritesheetID spr_id)
	: m_pos(pos)
	, m_spr_id(spr_id)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<AddProjectileCommand>(m_pos, m_spr_id); }

private:
    AbsolutePosition m_pos;
    SpritesheetID m_spr_id;
};



#endif /* COMMANDS_ADD_PROJECTILE_COMMAND_H_ */
