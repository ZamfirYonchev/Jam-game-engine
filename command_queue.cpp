/*
 * command_queue.cpp
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#include "command_queue.h"

void CommandQueue::process(Time time_diff)
{
    auto it = m_commands.begin();
    while(it != m_commands.end())
    {
		m_curr_cmd_it = it;
		(*it)->execute();
		it = m_commands.erase(it);
    }
}

