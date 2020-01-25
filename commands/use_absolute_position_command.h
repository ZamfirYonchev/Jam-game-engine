/*
 * use_absolute_position_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_ABSOLUTE_POSITION_COMMAND_H_
#define COMMANDS_USE_ABSOLUTE_POSITION_COMMAND_H_

#include "command.h"
#include "../components/absolute_position.h"

class UseAbsolutePositionCommand : public Command
{
public:
    UseAbsolutePositionCommand(const AbsolutePosition& position)
	: m_position(position) {}

    void execute() const;
    Command* clone() { return new UseAbsolutePositionCommand(m_position); }
private:
    AbsolutePosition m_position;
};


#endif /* COMMANDS_USE_ABSOLUTE_POSITION_COMMAND_H_ */
