/*
 * modify_health_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_HEALTH_COMMAND_H_
#define COMMANDS_MODIFY_HEALTH_COMMAND_H_

#include "command.h"

class ModifyHealthCommand : public Command
{
public:
	ModifyHealthCommand(double max_hp, double hp, double hp_change)
	: m_max_hp(max_hp)
	, m_hp(hp)
	, m_hp_change(hp_change)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<ModifyHealthCommand>(m_max_hp, m_hp, m_hp_change); }
private:
	double m_max_hp, m_hp, m_hp_change;
};


#endif /* COMMANDS_MODIFY_HEALTH_COMMAND_H_ */
