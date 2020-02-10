/*
 * modify_position_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_POSITION_COMMAND_H_
#define COMMANDS_MODIFY_POSITION_COMMAND_H_

#include "command.h"

class ModifyPositionCommand : public Command
{
public:
	ModifyPositionCommand(double x, double y, double w, double h)
	: m_x(x)
	, m_y(y)
	, m_w(w)
	, m_h(h)
	{}

	void execute() const;
	std::unique_ptr<Command> clone() { return std::make_unique<ModifyPositionCommand>(m_x, m_y, m_w, m_h); }
private:
    double m_x, m_y, m_w, m_h;
};


#endif /* COMMANDS_MODIFY_POSITION_COMMAND_H_ */
