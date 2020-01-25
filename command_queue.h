/*
 * command_queue.h
 *
 *  Created on: Nov 24, 2019
 *      Author: zamfi
 */

#ifndef COMMAND_QUEUE_H_
#define COMMAND_QUEUE_H_

#include "commands/command.h"
#include "commands/null_command.h"
#include <list>
#include "types.h"

class CommandQueue
{
public:
    CommandQueue() : m_curr_cmd_it(m_commands.end()) {}
    ~CommandQueue()
    {
        for(auto it = m_commands.begin(); it != m_commands.end(); ++it)
            delete *it;
    }
    CommandQueue(const CommandQueue& ) = delete;
    CommandQueue& operator=(const CommandQueue& ) = delete;

    CommandQueue(CommandQueue&& rhs)
    {
    	m_commands = std::move(rhs.m_commands);
    	m_curr_cmd_it = std::move(rhs.m_curr_cmd_it);
    }

    CommandQueue& operator=(CommandQueue&& rhs)
    {
    	clear();
    	m_commands = std::move(rhs.m_commands);
    	m_curr_cmd_it = rhs.m_curr_cmd_it;
    	return *this;
    }

    int size() const { return m_commands.size(); }

    void process(Time time_diff);

    void push(Command* cmd)
    {
        if(cmd != nullptr)
            m_commands.push_back(cmd);
    }

    void insert_next(Command* cmd)
    {
        if(cmd != nullptr)
            m_commands.insert(std::next(m_curr_cmd_it), cmd);
    }

    Command* pop_next()
    {
        auto it = std::next(m_curr_cmd_it);
        Command* cmd = *it;
        m_commands.erase(it);
        return cmd;
    }

    void clear()
    {
        for(auto it = m_commands.begin(); it != m_commands.end(); ++it)
            delete *it;

        m_commands.clear();
    }

    void flush_commands()
    {
        for(auto it = m_commands.begin(); it != m_commands.end(); ++it)
        	if(it != m_curr_cmd_it)
			{
				delete *it;
				*it = new NullCommand();
			}
    }

private:
    std::list<Command*> m_commands;
    std::list<Command*>::iterator m_curr_cmd_it;
};

#endif /* COMMAND_QUEUE_H_ */
