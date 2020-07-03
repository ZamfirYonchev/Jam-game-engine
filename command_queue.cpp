/*
 * command_queue.cpp
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#include "command_queue.h"

void CommandQueue::process(Time time_diff)
{
    while(m_commands.cbegin() != m_commands.cend())
    {
        auto cmd = std::move(m_commands.front());
        cmd->execute();
        m_commands.pop_front();
    }
}

