/*
 * modify_visuals_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_VISUALS_COMMAND_H_
#define COMMANDS_MODIFY_VISUALS_COMMAND_H_

#include "command.h"

class ModifyVisualsCommand : public Command
{
public:
	ModifyVisualsCommand(double render_state, double repeat_x, double repeat_y, double spr_id, double layer)
	: m_render_state(render_state)
	, m_repeat_x(repeat_x)
	, m_repeat_y(repeat_y)
	, m_spr_id(spr_id)
	, m_layer(layer)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<ModifyVisualsCommand>(m_render_state, m_repeat_x, m_repeat_y, m_spr_id, m_layer); }
private:
	double m_render_state, m_repeat_x, m_repeat_y, m_spr_id, m_layer;
};


#endif /* COMMANDS_MODIFY_VISUALS_COMMAND_H_ */
