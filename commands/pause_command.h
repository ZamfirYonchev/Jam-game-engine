/*
 * pause_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_PAUSE_COMMAND_H_
#define COMMANDS_PAUSE_COMMAND_H_

#include "command.h"

class PauseCommand : public Command
{
public:
    PauseCommand(bool paused) : m_paused(paused) {}
    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<PauseCommand>(m_paused); }
private:
    bool m_paused;
};


#endif /* COMMANDS_PAUSE_COMMAND_H_ */
