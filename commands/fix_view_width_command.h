/*
 * fix_view_width_command.h
 *
 *  Created on: May 23, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_FIX_VIEW_WIDTH_COMMAND_H_
#define COMMANDS_FIX_VIEW_WIDTH_COMMAND_H_


#include "command.h"
#include <string>

class FixViewWidthCommand : public Command
{
public:
	FixViewWidthCommand() = default;

    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<FixViewWidthCommand>(); }

private:
};



#endif /* COMMANDS_FIX_VIEW_WIDTH_COMMAND_H_ */
