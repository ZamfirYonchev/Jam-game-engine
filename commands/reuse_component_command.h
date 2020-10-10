/*
 * reuse_component_command.h
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_REUSE_COMPONENT_COMMAND_H_
#define COMMANDS_REUSE_COMPONENT_COMMAND_H_

#include "command.h"
#include "../types.h"
#include <SDL2/SDL.h>

template<typename T>
class ReuseComponentCommand : public Command
{
public:
	ReuseComponentCommand(const EntityID& source_id, SDL_Renderer* renderer)
	: m_source_id(source_id)
	, m_renderer(renderer)
	{}

    void execute() const;

	std::unique_ptr<Command> clone() const { return std::make_unique<ReuseComponentCommand>(m_source_id, m_renderer); }

private:
    EntityID m_source_id;
    SDL_Renderer* m_renderer;
};
#endif /* COMMANDS_REUSE_COMPONENT_COMMAND_H_ */
