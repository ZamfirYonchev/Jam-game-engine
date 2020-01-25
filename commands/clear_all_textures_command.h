/*
 * clear_all_textures_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_ALL_TEXTURES_COMMAND_H_
#define COMMANDS_CLEAR_ALL_TEXTURES_COMMAND_H_

#include "command.h"

class ClearAllTexturesCommand : public Command
{
public:
	ClearAllTexturesCommand() {}
    void execute() const;
    Command* clone() { return new ClearAllTexturesCommand(); }
};


#endif /* COMMANDS_CLEAR_ALL_TEXTURES_COMMAND_H_ */
