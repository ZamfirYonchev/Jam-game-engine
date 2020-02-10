/*
 * use_attached_position_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_ATTACHED_POSITION_COMMAND_H_
#define COMMANDS_USE_ATTACHED_POSITION_COMMAND_H_

#include "command.h"
#include "../globals.h"

class UseAttachedPositionCommand : public Command
{
public:
	UseAttachedPositionCommand(EntityID id, double offset_x, double offset_y, double offset_w, double offset_h)
	: m_id(id)
	, m_offset_x(offset_x)
	, m_offset_y(offset_y)
	, m_offset_w(offset_w)
	, m_offset_h(offset_h)
	{}

	void execute() const;
	std::unique_ptr<Command> clone() { return std::make_unique<UseAttachedPositionCommand>(m_id, m_offset_x, m_offset_y, m_offset_w, m_offset_h); }
private:
    EntityID m_id;
    double m_offset_x, m_offset_y, m_offset_w, m_offset_h;
};

#endif /* COMMANDS_USE_ATTACHED_POSITION_COMMAND_H_ */
