/*
 * use_normal_interaction_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_NORMAL_INTERACTION_COMMAND_H_
#define COMMANDS_USE_NORMAL_INTERACTION_COMMAND_H_

#include "command.h"
#include "cinttypes"

class UseNormalInteractionCommand : public Command
{
public:
	UseNormalInteractionCommand(int32_t group_vec)
	: m_group_vec(group_vec)
	{}

	void execute() const;
    Command* clone() { return new UseNormalInteractionCommand(m_group_vec); }

private:
    int32_t m_group_vec;
};


#endif /* COMMANDS_USE_NORMAL_INTERACTION_COMMAND_H_ */
