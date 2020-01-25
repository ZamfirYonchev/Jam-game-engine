/*
 * use_constant_control_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_CONSTANT_CONTROL_COMMAND_H_
#define COMMANDS_USE_CONSTANT_CONTROL_COMMAND_H_

#include "command.h"
#include "../components/control.h"

class UseConstantControlCommand : public Command
{
public:
	UseConstantControlCommand(int8_t move_dec, bool jump_dec, Control::LookDir look_dir)
	: m_move_decision(move_dec)
	, m_jump_decision(jump_dec)
	, m_look_dir(look_dir)
	{}

    void execute() const;
    Command* clone() { return new UseConstantControlCommand(m_move_decision, m_jump_decision, m_look_dir); }
private:
	int8_t m_move_decision;
	bool m_jump_decision;
	Control::LookDir m_look_dir;
};


#endif /* COMMANDS_USE_CONSTANT_CONTROL_COMMAND_H_ */
