/*
 * use_input_control_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_INPUT_CONTROL_COMMAND_H_
#define COMMANDS_USE_INPUT_CONTROL_COMMAND_H_

#include "command.h"
#include "../types.h"

class UseInputControlCommand : public Command
{
public:
	UseInputControlCommand(ProcedureID shoot_id, double shoot_cooldown)
	: m_shoot_id(shoot_id)
	, m_shoot_cooldown(shoot_cooldown)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseInputControlCommand>(m_shoot_id, m_shoot_cooldown); }
private:
    ProcedureID m_shoot_id;
    double m_shoot_cooldown;
};

#endif /* COMMANDS_USE_INPUT_CONTROL_COMMAND_H_ */
