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
#include <SDL2/SDL.h>
#include <istream>

class CommandQueue
{
public:
	CommandQueue() = default;
    ~CommandQueue() = default;

    CommandQueue(const CommandQueue& ) = delete;
    CommandQueue& operator=(const CommandQueue& ) = delete;

    CommandQueue(CommandQueue&& rhs) noexcept : m_commands(std::move(rhs.m_commands)) {}

    CommandQueue& operator=(CommandQueue&& rhs) noexcept
    {
    	clear();
    	m_commands = std::move(rhs.m_commands);
    	return *this;
    }

    int size() const { return m_commands.size(); }

    void process(Time time_diff);
    void process_stream(std::istream& input, SDL_Renderer* renderer);

    void push(std::unique_ptr<Command> cmd)
    {
		m_commands.push_back(std::move(cmd));
    }

    void insert_next(std::unique_ptr<Command> cmd)
    {
		m_commands.push_front(std::move(cmd));
    }

    void insert_before(const std::list<std::unique_ptr<Command>>::iterator it, std::unique_ptr<Command> cmd)
    {
    	m_commands.insert(it, std::move(cmd));
    }

    std::unique_ptr<Command> pop_next()
    {
        //TODO check m_commands not empty
        std::unique_ptr<Command> cmd = std::move(m_commands.front());
        m_commands.pop_front();
        return cmd;
    }

    void clear()
    {
        m_commands.clear();
    }

    void flush_commands(const bool flush_first_command)
    {
        for(auto it = m_commands.begin(); it != m_commands.end(); ++it)
        	if(it != m_commands.begin() || flush_first_command)
			{
				*it = std::make_unique<NullCommand>();
			}
    }

private:
    std::list<std::unique_ptr<Command>> m_commands;
};

#endif /* COMMAND_QUEUE_H_ */
