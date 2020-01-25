/*
 * modify_control_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_CONTROL_COMMAND_H_
#define COMMANDS_MODIFY_CONTROL_COMMAND_H_

#include "command.h"

class ModifyControlCommand : public Command
{
public:
	ModifyControlCommand(double decision_jump, double decision_duck, double decision_attack, double decision_walk, double look_dir)
	: m_decision_jump(decision_jump)
	, m_decision_duck(decision_duck)
	, m_decision_attack(decision_attack)
	, m_decision_walk(decision_walk)
	, m_look_dir(look_dir)
	{}

	void execute() const;
	Command* clone() { return new ModifyControlCommand(m_decision_jump, m_decision_duck, m_decision_attack, m_decision_walk, m_look_dir); }
private:
    double m_decision_jump;
    double m_decision_duck;
    double m_decision_attack;
    double m_decision_walk;
    double m_look_dir;
};


#endif /* COMMANDS_MODIFY_CONTROL_COMMAND_H_ */
