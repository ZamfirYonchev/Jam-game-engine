/*
 * use_health_visuals_command.h
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_HEALTH_VISUALS_COMMAND_H_
#define COMMANDS_USE_HEALTH_VISUALS_COMMAND_H_

#include "command.h"
#include "../types.h"

class UseHealthVisualsCommand : public Command
{
public:
	UseHealthVisualsCommand(SpritesheetID spr_id, uint16_t repeat_x)
	: m_spr_id(spr_id)
	, m_repeat_x(repeat_x)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseHealthVisualsCommand>(m_spr_id, m_repeat_x); }
private:
    SpritesheetID m_spr_id;
    uint16_t m_repeat_x;
};


#endif /* COMMANDS_USE_HEALTH_VISUALS_COMMAND_H_ */
