/*
 * command.h
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_COMMAND_H_
#define COMMANDS_COMMAND_H_

#include <memory>

class Command
{
public:
    virtual ~Command() {}
    virtual void execute() const = 0;
    virtual std::unique_ptr<Command> clone() const = 0;
};

#endif /* COMMANDS_COMMAND_H_ */
