/*
 * use_character_health_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_CHARACTER_HEALTH_COMMAND_H_
#define COMMANDS_USE_CHARACTER_HEALTH_COMMAND_H_

#include "command.h"

class UseCharacterHealthCommand : public Command
{
public:
	UseCharacterHealthCommand(double hp, double max_hp)
	: m_hp(hp)
	, m_max_hp(max_hp)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseCharacterHealthCommand>(m_hp, m_max_hp); }
private:
    double m_hp, m_max_hp;
};


#endif /* COMMANDS_USE_CHARACTER_HEALTH_COMMAND_H_ */
