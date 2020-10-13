/*
 * add_character_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_CHARACTER_COMMAND_H_
#define COMMANDS_ADD_CHARACTER_COMMAND_H_

#include "command.h"
#include "../types.h"
#include "../components/absolute_position.h"

class AddCharacterCommand : public Command
{
public:
    AddCharacterCommand(const AbsolutePosition& pos, double hp, SpritesheetID spr_id)
	: m_pos(pos)
	, m_hp(hp)
	, m_spr_id(spr_id)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<AddCharacterCommand>(m_pos, m_hp, m_spr_id); }

private:
    AbsolutePosition m_pos;
    double m_hp;
    SpritesheetID m_spr_id;
};



#endif /* COMMANDS_ADD_CHARACTER_COMMAND_H_ */
