/*
 * use_attached_health_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_ATTACHED_HEALTH_COMMAND_H_
#define COMMANDS_USE_ATTACHED_HEALTH_COMMAND_H_

#include "command.h"
#include "../types.h"

class UseAttachedHealthCommand : public Command
{
public:
	UseAttachedHealthCommand(EntityID attached_id, double offset_hp, double offset_max_hp)
	: m_attached_id(attached_id)
	, m_offset_hp(offset_hp)
	, m_offset_max_hp(offset_max_hp)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseAttachedHealthCommand>(m_attached_id, m_offset_hp, m_offset_max_hp); }
private:
    EntityID m_attached_id;
    double m_offset_hp, m_offset_max_hp;
};


#endif /* COMMANDS_USE_ATTACHED_HEALTH_COMMAND_H_ */
