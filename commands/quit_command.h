/*
 * quit_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_QUIT_COMMAND_H_
#define COMMANDS_QUIT_COMMAND_H_

#include "command.h"

class QuitCommand : public Command
{
public:
    QuitCommand() {}
    void execute() const;
    Command* clone() { return new QuitCommand(); }
};


#endif /* COMMANDS_QUIT_COMMAND_H_ */
