/*
 * clear_all_spritesheets_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_CLEAR_ALL_SPRITESHEETS_COMMAND_H_
#define COMMANDS_CLEAR_ALL_SPRITESHEETS_COMMAND_H_

#include "command.h"

class ClearAllSpritesheetsCommand : public Command
{
public:
	ClearAllSpritesheetsCommand() {}
    void execute() const;
    Command* clone() { return new ClearAllSpritesheetsCommand(); }
};

#endif /* COMMANDS_CLEAR_ALL_SPRITESHEETS_COMMAND_H_ */
