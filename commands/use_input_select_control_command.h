/*
 * use_input_select_control_command.h
 *
 *  Created on: Nov 26, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_INPUT_SELECT_CONTROL_COMMAND_H_
#define COMMANDS_USE_INPUT_SELECT_CONTROL_COMMAND_H_

#include "command.h"
#include "../types.h"

class UseInputSelectControlCommand : public Command
{
public:
	UseInputSelectControlCommand(int select, int max, ProcedureID proc_id)
	: m_select(select)
	, m_max(max)
	, m_proc_id(proc_id)
	{}

    void execute() const;
    Command* clone() { return new UseInputSelectControlCommand(m_select, m_max, m_proc_id); }
private:
    int m_select;
    int m_max;
    ProcedureID m_proc_id;
};


#endif /* COMMANDS_USE_INPUT_SELECT_CONTROL_COMMAND_H_ */
