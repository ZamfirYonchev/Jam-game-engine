/*
 * add_spritesheet_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_ADD_SPRITESHEET_COMMAND_H_
#define COMMANDS_ADD_SPRITESHEET_COMMAND_H_

#include "command.h"
#include "../spritesheet.h"

class AddSpritesheetCommand : public Command
{
public:
    AddSpritesheetCommand(const Spritesheet& spritesheet) : m_spritesheet(spritesheet) {}

    void execute() const;
    std::unique_ptr<Command> clone() const { return std::make_unique<AddSpritesheetCommand>(m_spritesheet); }

private:
    Spritesheet m_spritesheet;
};

#endif /* COMMANDS_ADD_SPRITESHEET_COMMAND_H_ */
